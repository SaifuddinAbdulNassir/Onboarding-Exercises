#include "ndpi/NdpiProcessor.h"

// Library includes
#include <cxxopts/cxxopts.hpp>
#include <libfort/fort.hpp>
#include <pcapplusplus/IPv4Layer.h>
#include <pcapplusplus/PcapLiveDeviceList.h>
#include <pcapplusplus/TcpLayer.h>
#include <pcapplusplus/UdpLayer.h>

// Project includes
#include "ndpi/NdpiCaptureCookie.h"
#include "ndpi/NdpiConnectionInfo.h"
#include "ndpi/NdpiConnectionKey.h"
#include "ndpi/NdpiSignalHandler.h"

using namespace cxxopts;
using namespace fort;
using namespace ndpi;
using namespace pcpp;
using namespace std;

// Constructors & destructors
NdpiProcessor::NdpiProcessor()
{
}

NdpiProcessor::~NdpiProcessor()
{
}

// Business logic

void NdpiProcessor::canonicalize(uint32_t &srcIp, uint32_t &dstIp, uint16_t &srcPort, uint16_t &dstPort)
{
    // Ensure consistent ordering of IP addresses and ports for flow identification
    if (srcIp > dstIp || (srcIp == dstIp && srcPort > dstPort))
    {
        swap(srcIp, dstIp);
        swap(srcPort, dstPort);
    }
}

void NdpiProcessor::onPacketArrives(RawPacket *rawPacket, PcapLiveDevice *dev, void *userData)
{
    // Unpack cookie
    auto cookie = static_cast<NdpiCaptureCookie *>(userData);
    auto ndpiMod = get<0>(*cookie);
    NdpiState &appState = *get<1>(*cookie);
    NdpiConnectionsMap &connectionMap = *get<2>(*cookie);

    // Parse packet
    Packet packet(rawPacket);
    auto ip = packet.getLayerOfType<IPv4Layer>();
    if (!ip)
        return;

    auto l4Proto = ip->getIPv4Header()->protocol;
    uint16_t srcPort = 0, dstPort = 0;

    // Only process TCP and UDP packets
    if (l4Proto == IPPROTO_TCP)
    {
        auto tcp = packet.getLayerOfType<TcpLayer>();
        if (!tcp)
            return;

        // Extract ports
        srcPort = tcp->getTcpHeader()->portSrc;
        dstPort = tcp->getTcpHeader()->portDst;
    }
    else if (l4Proto == IPPROTO_UDP)
    {
        auto udp = packet.getLayerOfType<UdpLayer>();
        if (!udp)
            return;

        srcPort = udp->getUdpHeader()->portSrc;
        dstPort = udp->getUdpHeader()->portDst;
    }
    else
    {
        return;
    }

    // Extract IP addresses
    auto srcIp = ip->getSrcIPv4Address().toInt();
    auto dstIp = ip->getDstIPv4Address().toInt();

    // Canonicalize flow
    canonicalize(srcIp, dstIp, srcPort, dstPort);

    // Create connection key
    auto key = NdpiConnectionKey(dstIp, dstPort, l4Proto, srcIp, srcPort);

    // Lookup or create connection info
    auto it = connectionMap.find(key);
    if (it == connectionMap.end())
    {
        // First time seeing this flow, create new ConnectionInfo
        auto insertResult = connectionMap.try_emplace(key, NdpiConnectionInfo{});
        it = insertResult.first;
        NdpiConnectionInfo &connectionInfo = it->second;
        connectionInfo.setUid(appState.getUid());
        appState.incrementUid();
        connectionInfo.setFlow((ndpi_flow_struct *)calloc(1, ndpi_detection_get_sizeof_ndpi_flow_struct()));
        connectionInfo.setPacketCount(0);
        connectionInfo.setDone(false);
        connectionInfo.setProtocol("UNKNOWN");
        connectionInfo.setCategory("UNKNOWN");
        connectionInfo.setDomain("");
        return;
    }

    // Existing flow, update ConnectionInfo
    NdpiConnectionInfo &connectionInfo = it->second;

    // If we've already identified the protocol or exceeded max packets, skip further processing
    if (connectionInfo.getDone())
        return;

    // Update packet count and check if we should give up on this flow
    connectionInfo.setPacketCount(connectionInfo.getPacketCount() + 1);
    if (connectionInfo.getPacketCount() > maxPackets)
    {
        connectionInfo.setProtocol("UNKNOWN");
        connectionInfo.setCategory("UNKNOWN");
        connectionInfo.setDomain("");
        connectionInfo.setDone(true);
        return;
    }

    // Prepare nDPI input info
    ndpi_flow_input_info inputInfo{};

    // Determine packet direction (client → server or server → client)
    bool isForward =
        (ip->getSrcIPv4Address().toInt() == key.getSrcIp() &&
         srcPort == key.getSrcPort());

    // 0 = client → server, 1 = server → client
    inputInfo.in_pkt_dir = (isForward) ? 0 : 1;

    // Mark if this is the first packet of the flow (seen_flow_beginning)
    inputInfo.seen_flow_beginning = (connectionInfo.getPacketCount() == 1);

    // Calculate packet timestamp in milliseconds
    auto timeMs =
        rawPacket->getPacketTimeStamp().tv_sec * 1000ULL +
        rawPacket->getPacketTimeStamp().tv_nsec / 1000000ULL;

    // Feed packet data to nDPI for protocol detection
    const auto ipData = ip->getData();
    auto ipLen = ip->getDataLen();

    // nDPI will update the flow struct and return the detected protocol (if any)
    auto proto = ndpi_detection_process_packet(ndpiMod, connectionInfo.getFlow(), ipData, ipLen, timeMs, &inputInfo);

    // If nDPI identified the protocol, update ConnectionInfo accordingly
    if (proto.proto.app_protocol != NDPI_PROTOCOL_UNKNOWN)
    {
        connectionInfo.setProtocol(ndpi_get_proto_name(ndpiMod, proto.proto.app_protocol));
        connectionInfo.setCategory(ndpi_category_get_name(ndpiMod, proto.category));
        if (connectionInfo.getFlow()->host_server_name[0] != '\0')
        {
            connectionInfo.setDomain(connectionInfo.getFlow()->host_server_name);
        }
        connectionInfo.setDone(true);
    }
}

bool NdpiProcessor::ParseArgs(int argc, char *argv[])
{
    try
    {
        // Define command line options
        Options options("ndpi-dpi", "A simple nDPI-based DPI application");

        options.add_options()("i,interface", "Interface to capture on", value<string>())("N,max-packets", "Maximum number of packets to process per flow", value<size_t>())("h,help", "sudo ./build/ndpi_dpi -i <Network Interface> -N <max packets per flow>");

        // Parse command line arguments
        auto result = options.parse(argc, argv);

        if (result.count("help"))
        {
            cout << options.help() << endl;
            return false;
        }

        if (!result.count("interface"))
        {
            cerr << "Interface is required\n";
            cout << options.help() << endl;
            return false;
        }

        // Set class members based on parsed arguments
        if (result.count("interface"))
            interface = result["interface"].as<string>();
        if (result.count("max-packets"))
            maxPackets = result["max-packets"].as<size_t>();
    }
    catch (const OptionException &e)
    {
        cerr << "Error parsing options: " << e.what() << endl;
        return false;
    }

    return true;
}

void NdpiProcessor::printResults(const NdpiConnectionsMap &connectionMap) const
{
    // Print results using libfort
    utf8_table table;
    table.set_border_style(FT_EMPTY_STYLE);

    table << endr;
    table << "ConnectionId" << "Protocol" << "Category" << "Domain" << endr;
    for (const auto &[key, info] : connectionMap)
    {
        table << info.getUid() << info.getProtocol() << info.getCategory() << info.getDomain() << endr;
    }
    cout << table.to_string();
}

void NdpiProcessor::processLivePackets()
{
    NdpiState ndpiState;
    NdpiConnectionsMap connectionMap;

    // Handle Ctrl+C signal
    NdpiSignalHandler signalHandler;
    auto ndpiMod = signalHandler.handleSignal();

    // Open live device for packet capture
    auto *dev = PcapLiveDeviceList::getInstance().getDeviceByName(interface);

    if (!dev || !dev->open())
    {
        cerr << "Cannot open device\n";
        return;
    }

    // Cookie to pass to packet handler
    NdpiCaptureCookie cookie{ndpiMod, &ndpiState, &connectionMap};

    // Start capturing packets
    dev->startCapture([this](RawPacket *rawPacket, PcapLiveDevice *dev, void *userData)
                      { this->onPacketArrives(rawPacket, dev, userData); }, &cookie);

    // Wait for Ctrl+C signal
    signalHandler.waitForSignal(ndpiState);

    // Stop capturing and close the device
    dev->stopCapture();
    dev->close();

    printResults(connectionMap);
}
