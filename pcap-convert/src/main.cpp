// Standard includes
#include <iostream>

// Library includes
#include <arpa/inet.h>
#include <pcapplusplus/DnsLayer.h>
#include <pcapplusplus/EthLayer.h>
#include <pcapplusplus/IPv4Layer.h>
#include <pcapplusplus/IPv6Layer.h>
#include <pcapplusplus/Packet.h>
#include <pcapplusplus/PcapFileDevice.h>
#include <pcapplusplus/UdpLayer.h>
#include <pcapplusplus/VlanLayer.h>

// Project includes
#include "Config.h"
#include "NetworkStats.h"

using namespace pcpp;
using namespace std;
using namespace pcapconvert;

// Command line argument parser

bool parseArgs(int argc, char *argv[], Config &config)
{
    for(int i = 1; i < argc; ++i)
    {
        string arg = argv[i];

        if(arg == "--vlan" && i + 1 < argc)
            config.setVlan(stoi(argv[++i]));
        else if(arg == "-ip-version" && i + 1 < argc)
            config.setIpVersion(stoi(argv[++i]));
        else if(arg == "--ttl" && i + 1 < argc)
            config.setTtlDec(stoi(argv[++i]));
        else if(arg == "--dns-addr" && i + 1 < argc)
            config.setDnsAddr(argv[++i]);
        else if(arg == "--dns-port" && i + 1 < argc)
            config.setDnsPort(stoi(argv[++i]));
        else if(arg == "-i" && i + 1 < argc)
            config.setInputFile(argv[++i]);
        else if(arg == "-o" && i + 1 < argc)
            config.setOutputFile(argv[++i]);
        else if(arg == "-h" || arg == "--help")
        {
            cout << "Command to run the App: ./build/pcap-convert [--vlan <vlan id>] [-ip-version <4|6>] [--ttl <decrement>] " <<
            "[--dns-addr <address>] [--dns-port <port>]  -i Pcapfiles/<input pcap file> -o Pcapfiles/<output pcap file>  \n";
        }
}

    return !config.getInputFile().empty() && !config.getOutputFile().empty();
}

int main(int argc, char *argv[])
{
    Config config;

    if(!parseArgs(argc, argv, config))
    {
        cerr << "Invalid arguments\n";
        return 1;
    }

    PcapFileReaderDevice reader(config.getInputFile());
    if(!reader.open())
    {
        cerr << "Cannot open input file\n";
        return 1;
    }

    PcapFileWriterDevice writer(config.getOutputFile(), reader.getLinkLayerType());
    if(!writer.open())
    {
        cerr << "Cannot open output file\n";
        return 1;
    }

    RawPacket raw;
    NetworkStats stats;

    while(reader.getNextPacket(raw))
    {
        stats.incrementTotalPackets();
        stats.addBytesIn(raw.getRawDataLen());

        Packet pkt(&raw);

        // VLAN filter
        if(config.getVlan() >= 0)
        {
            auto *vlan = pkt.getLayerOfType<VlanLayer>();
            if(!vlan || vlan->getVlanID() != config.getVlan())
            {
                stats.incrementDroppedPackets();
                stats.addBytesDropped(raw.getRawDataLen());
                continue;
            }
        }

        // Ethernet
        if(!pkt.isPacketOfType(Ethernet))
        {
            stats.incrementDroppedPackets();
            stats.addBytesDropped(raw.getRawDataLen());
            continue;
        }

        // IP version filter
        if(config.getIpVersion() >= 0 && ((config.getIpVersion() == 4 && !pkt.isPacketOfType(IPv4)) ||
            (config.getIpVersion() == 6 && !pkt.isPacketOfType(IPv6))))
        {
            stats.incrementDroppedPackets();
            stats.addBytesDropped(raw.getRawDataLen());
            continue;
        }

        // TTL handling
        auto *ip4 = pkt.getLayerOfType<IPv4Layer>();
        auto *ip6 = pkt.getLayerOfType<IPv6Layer>();
        if(ip4 && config.getTtlDec() >= 0)
        {
            if(ip4->getIPv4Header()->timeToLive <= config.getTtlDec() || ip4->getIPv4Header()->protocol == PACKETPP_IPPROTO_ICMP)
            {
                stats.incrementDroppedPackets();
                stats.addBytesDropped(raw.getRawDataLen());
                continue;
            }
            ip4->getIPv4Header()->timeToLive -= config.getTtlDec();
        }
        else if(ip6 && config.getTtlDec() >= 0)
        {
            if(ip6->getIPv6Header()->hopLimit <= config.getTtlDec() || ip6->getIPv6Header()->nextHeader == PACKETPP_IPPROTO_ICMPV6)
            {
                stats.incrementDroppedPackets();
                stats.addBytesDropped(raw.getRawDataLen());
                continue;
            }
            ip6->getIPv6Header()->hopLimit -= config.getTtlDec();
        }

        // DNS modification
        if(pkt.isPacketOfType(UDP))
        {
            auto *dns = pkt.getLayerOfType<DnsLayer>();
            auto *udp = pkt.getLayerOfType<UdpLayer>();

            if(dns && udp)
            {
                if(!config.getDnsAddr().empty())
                {
                    if(auto *ip4 = pkt.getLayerOfType<IPv4Layer>())
                    {
                        ip4->getIPv4Header()->ipDst = IPv4Address(config.getDnsAddr()).toInt();
                    }
                    else if(auto *ip6 = pkt.getLayerOfType<IPv6Layer>())
                    {
                        memcpy(ip6->getIPv6Header()->ipDst,
                            IPv6Address(config.getDnsAddr()).toBytes(), 16);
                    }
                }

                if(config.getDnsPort() > 0)
                    udp->getUdpHeader()->portDst = htons(config.getDnsPort());

                stats.incrementDnsModifiedPackets();
            }
        }

        pkt.computeCalculateFields();
        writer.writePacket(raw);

        stats.incrementWrittenPackets();
        stats.addBytesOut(raw.getRawDataLen());
    }

    cout << "Total bytes & packets processed: " << stats.getBytesIn() << "&" << stats.getTotalPackets() << "\n";
    cout << "Total bytes & packets dropped: " << stats.getBytesDropped() << "&" << stats.getDroppedPackets() << "\n";
    cout << "Total bytes & packets written: " << stats.getBytesOut() << "&" << stats.getWrittenPackets() << "\n";
    cout << "DNS modified: " << stats.getDnsModifiedPackets() << "\n";

    return 0;
}
