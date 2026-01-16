#include <csignal>
#include <cstring>
#include <iostream>
#include <unordered_map>

#include <pcapplusplus/EthLayer.h>
#include <pcapplusplus/IPv4Layer.h>
#include <pcapplusplus/Packet.h>
#include <pcapplusplus/PcapLiveDevice.h>
#include <pcapplusplus/PcapLiveDeviceList.h>
#include <pcapplusplus/TcpLayer.h>
#include <pcapplusplus/UdpLayer.h>

#include "structs/ConnectionInfo.h" 
#include "structs/ConnKeyStruct.h"

using namespace pcpp;

static bool g_running = true;
static uint64_t g_uid = 1;
static uint32_t g_max_packets = 100;

static std::unordered_map<ConnKey, ConnectionInfo, ConnKeyHash> g_connections;

// Signal Handler
void sigint_handler(int)
{
    g_running = false;
}

static void canonicalize(
    uint32_t& src_ip, uint32_t& dst_ip,
    uint16_t& src_port, uint16_t& dst_port)
{
    if(src_ip > dst_ip ||
       (src_ip == dst_ip && src_port > dst_port))
    {
        std::swap(src_ip, dst_ip);
        std::swap(src_port, dst_port);
    }
}

// Packet Handler
void onPacketArrives(pcpp::RawPacket* rawPacket,
                     pcpp::PcapLiveDevice* dev,
                     void* userData)
{
    auto* ndpi_mod = (ndpi_detection_module_struct*)userData;

    pcpp::Packet packet(rawPacket);
    auto* ip = packet.getLayerOfType<pcpp::IPv4Layer>();
    if(!ip)
    {
        return;
    }

    uint8_t l4_proto = ip->getIPv4Header()->protocol;
    uint16_t src_port = 0, dst_port = 0;

    if(l4_proto == IPPROTO_TCP)
    {
        auto* tcp = packet.getLayerOfType<pcpp::TcpLayer>();
        if(!tcp)
        {
            return;
        }
        src_port = ntohs(tcp->getTcpHeader()->portSrc);
        dst_port = ntohs(tcp->getTcpHeader()->portDst);
    }
    else if(l4_proto == IPPROTO_UDP)
    {
        auto* udp = packet.getLayerOfType<pcpp::UdpLayer>();
        if(!udp)
        {
            return;
        }
        src_port = ntohs(udp->getUdpHeader()->portSrc);
        dst_port = ntohs(udp->getUdpHeader()->portDst);
    }
    else
    {
        return;
    }

    uint32_t src_ip = ip->getSrcIPv4Address().toInt();
    uint32_t dst_ip = ip->getDstIPv4Address().toInt();

    uint16_t sport = src_port;
    uint16_t dport = dst_port;

    // Canonicalize flow
    canonicalize(src_ip, dst_ip, sport, dport);

    ConnKey key {
        ip->getSrcIPv4Address().toInt(),
        ip->getDstIPv4Address().toInt(),
        src_port,
        dst_port,
        l4_proto
    };

    auto it = g_connections.find(key);
    if(it == g_connections.end())
    {
        ConnectionInfo ci {};
        ci.uid = g_uid++;
        ci.flow = (ndpi_flow_struct*)calloc(
        1,
        ndpi_detection_get_sizeof_ndpi_flow_struct()
        );
        ci.packet_count = 0;
        ci.done = false;
        ci.protocol = "UNKNOWN";
        ci.category = "UNKNOWN";
        ci.domain = "";
        g_connections.emplace(key, ci);
        it = g_connections.find(key);
    }

    ConnectionInfo& conn = it->second;
    if(conn.done)
    {
        return;
    }

    conn.packet_count++;
    if(conn.packet_count > g_max_packets)
    {
        conn.protocol = "UNKNOWN";
        conn.category = "UNKNOWN";
        conn.domain = "";
        conn.done = true;
        return;
    }

    ndpi_flow_input_info input_info;
    memset(&input_info, 0, sizeof(input_info));
    bool is_forward =
    (ip->getSrcIPv4Address().toInt() == key.src_ip &&
     src_port == key.src_port);

    input_info.in_pkt_dir = (is_forward) ? 0 : 1; // 0 = client → server
    input_info.seen_flow_beginning = (conn.packet_count == 1);;

    uint64_t time_ms =
    rawPacket->getPacketTimeStamp().tv_sec * 1000ULL +
    rawPacket->getPacketTimeStamp().tv_nsec / 1000000ULL;

    const uint8_t* ip_data = ip->getData();
    uint16_t ip_len = ip->getDataLen();

    ndpi_protocol proto = ndpi_detection_process_packet(
        ndpi_mod,
        conn.flow,
        ip_data,
        ip_len,
        time_ms,
        &input_info
    );

    if(proto.proto.app_protocol != NDPI_PROTOCOL_UNKNOWN)
    {
        conn.protocol = ndpi_get_proto_name(ndpi_mod, proto.proto.app_protocol);
        conn.category =
            ndpi_category_get_name(ndpi_mod, proto.category);
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
        std::cerr << "Usage: " << argv[0]
                  << " -i <interface> [--N packets]\n";
        return 1;
    }

    std::string iface;
    for(int i = 1; i < argc; i++)
    {
        if(!strcmp(argv[i], "-i"))
        {
            iface = argv[++i];
        }
        else if(!strcmp(argv[i], "--N"))
        {
            g_max_packets = atoi(argv[++i]);
        }
    }

    signal(SIGINT, sigint_handler);

    struct ndpi_global_context *g_ctx = ndpi_global_init();
    ndpi_detection_module_struct *ndpi_mod =
        ndpi_init_detection_module(g_ctx);

    if(!ndpi_mod)
    {
        std::cerr << "nDPI init failed\n";
        exit(1);
    }
        
    ndpi_finalize_initialization(ndpi_mod);

    auto* dev =
        pcpp::PcapLiveDeviceList::getInstance().getDeviceByName(iface);

    if(!dev || !dev->open())
    {
        std::cerr << "Cannot open device\n";
        return 1;
    }

    dev->startCapture(onPacketArrives, ndpi_mod);

    while(g_running)
    {
        sleep(1);
    }

    dev->stopCapture();
    dev->close();

    std::cout << "\nConnectionId, Protocol, Category, Domain\n";
    for(const auto& kv : g_connections)
    {
        const auto& c = kv.second;
        std::cout << c.uid << ", "
                  << c.protocol << ", "
                  << c.category << ", "
                  << c.domain << "\n";
    }

    ndpi_exit_detection_module(ndpi_mod);
    return 0;
}
