// Standard includes
#include <csignal>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <poll.h>
#include <sys/signalfd.h>
#include <unistd.h>

// Library includes
#include <pcapplusplus/EthLayer.h>
#include <pcapplusplus/IPv4Layer.h>
#include <pcapplusplus/Packet.h>
#include <pcapplusplus/PcapLiveDevice.h>
#include <pcapplusplus/PcapLiveDeviceList.h>
#include <pcapplusplus/TcpLayer.h>
#include <pcapplusplus/UdpLayer.h>

// Project includes
#include "CaptureCookie.h"

using namespace ndpi;
using namespace pcpp;
using namespace std;

//  Connection functions

static void canonicalize(uint32_t &srcIp, uint32_t &dstIp, uint16_t &srcPort, uint16_t &dstPort)
{
    if (srcIp > dstIp || (srcIp == dstIp && srcPort > dstPort))
    {
        swap(srcIp, dstIp);
        swap(srcPort, dstPort);
    }
}

// Packet Handler

void onPacketArrives(RawPacket *rawPacket, PcapLiveDevice *dev, void *userData)
{
    auto *cookie = static_cast<CaptureCookie *>(userData);
    auto *ndpiMod = get<0>(*cookie);
    NdpiState &appState = *get<1>(*cookie);
    ConnectionsMap &connectionMap = *get<2>(*cookie);

    Packet packet(rawPacket);
    auto *ip = packet.getLayerOfType<IPv4Layer>();
    if (!ip)
        return;

    auto l4Proto = ip->getIPv4Header()->protocol;
    uint16_t srcPort = 0, dstPort = 0;

    if (l4Proto == IPPROTO_TCP)
    {
        auto *tcp = packet.getLayerOfType<TcpLayer>();
        if (!tcp)
            return;

        srcPort = ntohs(tcp->getTcpHeader()->portSrc);
        dstPort = ntohs(tcp->getTcpHeader()->portDst);
    }
    else if (l4Proto == IPPROTO_UDP)
    {
        auto *udp = packet.getLayerOfType<UdpLayer>();
        if (!udp)
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

    auto key = ConnectionKey(dstIp, dstPort, l4Proto, srcIp, srcPort);

    auto it = connectionMap.find(key);
    if (it == connectionMap.end())
    {
        auto insertResult = connectionMap.try_emplace(key, ConnectionInfo{});
        it = insertResult.first;
        ConnectionInfo &connectionInfo = it->second;
        connectionInfo.setUid(appState.getUid());
        appState.incrementUid();
        connectionInfo.setFlow((ndpi_flow_struct *)calloc(1, ndpi_detection_get_sizeof_ndpi_flow_struct()));
        connectionInfo.setPacketCount(0);
        connectionInfo.setDone(false);
        connectionInfo.setProtocol("UNKNOWN");
        connectionInfo.setCategory("UNKNOWN");
        connectionInfo.setDomain("");
    }

    ConnectionInfo &connectionInfo = it->second;
    if (connectionInfo.getDone())
        return;

    connectionInfo.setPacketCount(connectionInfo.getPacketCount() + 1);
    if (connectionInfo.getPacketCount() > appState.getMaxPackets())
    {
        connectionInfo.setProtocol("UNKNOWN");
        connectionInfo.setCategory("UNKNOWN");
        connectionInfo.setDomain("");
        connectionInfo.setDone(true);
        return;
    }

    ndpi_flow_input_info inputInfo;
    memset(&inputInfo, 0, sizeof(inputInfo));
    bool isForward =
        (ip->getSrcIPv4Address().toInt() == key.getSrcIp() &&
         srcPort == key.getSrcPort());

    // 0 = client → server
    inputInfo.in_pkt_dir = (isForward) ? 0 : 1;
    inputInfo.seen_flow_beginning = (connectionInfo.getPacketCount() == 1);

    auto timeMs =
        rawPacket->getPacketTimeStamp().tv_sec * 1000ULL +
        rawPacket->getPacketTimeStamp().tv_nsec / 1000000ULL;

    const auto *ipData = ip->getData();
    auto ipLen = ip->getDataLen();

    auto proto = ndpi_detection_process_packet(ndpiMod, connectionInfo.getFlow(), ipData, ipLen, timeMs, &inputInfo);

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

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cerr << "Usage: " << argv[0]
             << " -i <interface> [--N packets]\n";
        return 1;
    }

    string iface;
    NdpiState appState;
    ConnectionsMap connectionMap;
    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-i"))
        {
            iface = argv[++i];
        }
        else if (!strcmp(argv[i], "--N"))
        {
            appState.setMaxPackets(atoi(argv[++i]));
        }
    }

    // Handle Ctrl+C without globals: block SIGINT and consume it via signalfd
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    if (sigprocmask(SIG_BLOCK, &mask, nullptr) == -1)
    {
        perror("sigprocmask");
        return 1;
    }
    int sigFd = signalfd(-1, &mask, SFD_CLOEXEC);
    if (sigFd == -1)
    {
        perror("signalfd");
        return 1;
    }

    auto *ctx = ndpi_global_init();
    auto *ndpiMod = ndpi_init_detection_module(ctx);

    if (!ndpiMod)
    {
        cerr << "nDPI init failed\n";
        exit(1);
    }

    NDPI_PROTOCOL_BITMASK all;
    NDPI_BITMASK_SET_ALL(all);
    ndpi_set_protocol_detection_bitmask2(ndpiMod, &all);

    ndpi_finalize_initialization(ndpiMod);

    auto *dev = PcapLiveDeviceList::getInstance().getDeviceByName(iface);

    if (!dev || !dev->open())
    {
        cerr << "Cannot open device\n";
        return 1;
    }

    CaptureCookie cookie{ndpiMod, &appState, &connectionMap};
    dev->startCapture(onPacketArrives, &cookie);

    while (appState.getRunning())
    {
        pollfd pfd;
        pfd.fd = sigFd;
        pfd.events = POLLIN;
        pfd.revents = 0;

        int rc = poll(&pfd, 1, 1000);
        if (rc > 0 && (pfd.revents & POLLIN))
        {
            signalfd_siginfo si;
            ssize_t n = read(sigFd, &si, sizeof(si));
            if (n == (ssize_t)sizeof(si) && si.ssi_signo == SIGINT)
                appState.setRunning(false);
        }
    }

    dev->stopCapture();
    dev->close();
    close(sigFd);

    cout << "\nConnectionId, Protocol, Category, Domain\n";
    for (const auto &kv : connectionMap)
    {
        const auto &c = kv.second;
        cout << c.getUid() << ", "
             << c.getProtocol() << ", "
             << c.getCategory() << ", "
             << c.getDomain() << "\n";
    }

    ndpi_exit_detection_module(ndpiMod);
    return 0;
}
