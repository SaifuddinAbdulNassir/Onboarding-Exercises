// Standard includes
#include <csignal>
#include <cstring>
#include <iostream>

// Library includes
#include <pcapplusplus/EthLayer.h>
#include <pcapplusplus/IPv4Layer.h>
#include <pcapplusplus/Packet.h>
#include <pcapplusplus/PcapLiveDevice.h>
#include <pcapplusplus/PcapLiveDeviceList.h>
#include <pcapplusplus/TcpLayer.h>
#include <pcapplusplus/UdpLayer.h>

// Project includes
#include "ConnectionsMap.h"

// Declare the global connection map
ConnectionsMap connectionMap;

using namespace pcpp;
using namespace std;

static bool running = true;
static uint32_t maxPackets = 100;
static uint64_t uid = 1;

// Signal Handler

void sigint_handler(int)
{
    running = false;
}

// Make bidirectional flows use the same key

static void canonicalize(
    uint32_t& srcIp, uint32_t& dstIp,
    uint16_t& srcPort, uint16_t& dstPort)
{
    if(srcIp > dstIp ||
       (srcIp == dstIp && srcPort > dstPort))
    {
        swap(srcIp, dstIp);
        swap(srcPort, dstPort);
    }
}

// Packet Handler

void onPacketArrives(pcpp::RawPacket* rawPacket,
                     pcpp::PcapLiveDevice* dev,
                     void* userData)
{
    auto* ndpiMod = (ndpi_detection_module_struct*)userData;

    pcpp::Packet packet(rawPacket);
    auto* ip = packet.getLayerOfType<pcpp::IPv4Layer>();
    if(!ip)
        return;

    auto l4Proto = ip->getIPv4Header()->protocol;
    uint16_t srcPort = 0, dstPort = 0;

    if(l4Proto == IPPROTO_TCP)
    {
        auto* tcp = packet.getLayerOfType<pcpp::TcpLayer>();
        if(!tcp)
            return;

        srcPort = ntohs(tcp->getTcpHeader()->portSrc);
        dstPort = ntohs(tcp->getTcpHeader()->portDst);
    }
    else if(l4Proto == IPPROTO_UDP)
    {
        auto* udp = packet.getLayerOfType<pcpp::UdpLayer>();
        if(!udp)
            return;
        
        srcPort = ntohs(udp->getUdpHeader()->portSrc);
        dstPort = ntohs(udp->getUdpHeader()->portDst);
    }
    else
    {
        return;
    }

    auto srcIp = ip->getSrcIPv4Address().toInt();
    auto dstIp = ip->getDstIPv4Address().toInt();

    // Canonicalize flow
    canonicalize(srcIp, dstIp, srcPort, dstPort);

    ConnectionKey key {
        srcIp,
        dstIp,
        srcPort,
        dstPort,
        l4Proto
    };

    auto it = connectionMap.find(key);
    if(it == connectionMap.end())
    {
        ConnectionInfo ci {};
        ci.uid = uid++;
        ci.flow = (ndpi_flow_struct*)calloc(
        1,
        ndpi_detection_get_sizeof_ndpi_flow_struct()
        );
        ci.packetCount = 0;
        ci.done = false;
        ci.protocol = "UNKNOWN";
        ci.category = "UNKNOWN";
        ci.domain = "";
        connectionMap.emplace(key, ci);
        it = connectionMap.find(key);
    }

    ConnectionInfo& conn = it->second;
    if(conn.done)
        return;

    conn.packetCount++;
    if(conn.packetCount > maxPackets)
    {
        conn.protocol = "UNKNOWN";
        conn.category = "UNKNOWN";
        conn.domain = "";
        conn.done = true;
        return;
    }

    ndpi_flow_input_info inputInfo;
    memset(&inputInfo, 0, sizeof(inputInfo));
    bool isForward =
    (ip->getSrcIPv4Address().toInt() == key.srcIp &&
     srcPort == key.srcPort);

    inputInfo.in_pkt_dir = (isForward) ? 0 : 1; // 0 = client → server
    inputInfo.seen_flow_beginning = (conn.packetCount == 1);;

    auto timeMs =
    rawPacket->getPacketTimeStamp().tv_sec * 1000ULL +
    rawPacket->getPacketTimeStamp().tv_nsec / 1000000ULL;

    const auto* ipData = ip->getData();
    auto ipLen = ip->getDataLen();

    ndpi_protocol proto = ndpi_detection_process_packet(
        ndpiMod,
        conn.flow,
        ipData,
        ipLen,
        timeMs,
        &inputInfo
    );

    if(proto.proto.app_protocol != NDPI_PROTOCOL_UNKNOWN)
    {
        conn.protocol = ndpi_get_proto_name(ndpiMod, proto.proto.app_protocol);
        conn.category =
            ndpi_category_get_name(ndpiMod, proto.category);
        if(conn.flow->host_server_name[0] != '\0')
        {
            conn.domain = conn.flow->host_server_name;
        }
        conn.done = true;
    }
}

int main(int argc, char* argv[])
{
    if(argc < 3)
    {
        cerr << "Usage: " << argv[0]
                  << " -i <interface> [--N packets]\n";
        return 1;
    }

    string iface;
    for(int i = 1; i < argc; i++)
    {
        if(!strcmp(argv[i], "-i"))
        {
            iface = argv[++i];
        }
        else if(!strcmp(argv[i], "--N"))
        {
            maxPackets = atoi(argv[++i]);
        }
    }

    signal(SIGINT, sigint_handler);

    struct ndpi_global_context *ctx = ndpi_global_init();
    ndpi_detection_module_struct *ndpiMod =
        ndpi_init_detection_module(ctx);

    if(!ndpiMod)
    {
        cerr << "nDPI init failed\n";
        exit(1);
    }
        
    ndpi_finalize_initialization(ndpiMod);

    auto* dev =
        pcpp::PcapLiveDeviceList::getInstance().getDeviceByName(iface);

    if(!dev || !dev->open())
    {
        cerr << "Cannot open device\n";
        return 1;
    }

    dev->startCapture(onPacketArrives, ndpiMod);

    while(running)
    {
        sleep(1);
    }

    dev->stopCapture();
    dev->close();

    cout << "\nConnectionId, Protocol, Category, Domain\n";
    for(const auto& kv : connectionMap)
    {
        const auto& c = kv.second;
        cout << c.uid << ", "
                  << c.protocol << ", "
                  << c.category << ", "
                  << c.domain << "\n";
    }

    ndpi_exit_detection_module(ndpiMod);
    return 0;
}
