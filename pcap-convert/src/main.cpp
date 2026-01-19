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

using namespace pcpp;
using namespace std;

// Command line argument parser

bool parseArgs(int argc, char *argv[], Config& cfg)
{
    for(int i = 1; i < argc; ++i)
    {
        string arg = argv[i];

        if(arg == "--vlan" && i + 1 < argc)
            cfg.vlan = stoi(argv[++i]);
        else if(arg == "-ip-version" && i + 1 < argc)
            cfg.ipVersion = stoi(argv[++i]);
        else if(arg == "--ttl" && i + 1 < argc)
            cfg.ttlDec = stoi(argv[++i]);
        else if(arg == "--dns-addr" && i + 1 < argc)
            cfg.dnsAddr = argv[++i];
        else if(arg == "--dns-port" && i + 1 < argc)
            cfg.dnsPort = stoi(argv[++i]);
        else if(arg == "-i" && i + 1 < argc)
            cfg.inputFile = argv[++i];
        else if(arg == "-o" && i + 1 < argc)
            cfg.outputFile = argv[++i];
    }

    return !cfg.inputFile.empty() && !cfg.outputFile.empty();
}

int main(int argc, char *argv[])
{
    Config cfg;

    if(!parseArgs(argc, argv, cfg))
    {
        cerr << "Invalid arguments\n";
        return 1;
    }

    PcapFileReaderDevice reader(cfg.inputFile);
    if(!reader.open())
    {
        cerr << "Cannot open input file\n";
        return 1;
    }

    PcapFileWriterDevice writer(cfg.outputFile, reader.getLinkLayerType());
    if(!writer.open())
    {
        cerr << "Cannot open output file\n";
        return 1;
    }

    auto totalPkts = 0, dropped = 0, written = 0;
    auto bytesIn = 0, bytesOut = 0, bytesDropped = 0;
    auto dnsModified = 0;

    RawPacket raw;

    while(reader.getNextPacket(raw))
    {
        totalPkts++;
        bytesIn += raw.getRawDataLen();

        Packet pkt(&raw);

        // VLAN filter
        if(cfg.vlan >= 0)
        {
            auto *vlan = pkt.getLayerOfType<VlanLayer>();
            if(!vlan || vlan->getVlanID() != cfg.vlan)
            {
                dropped++;
                bytesDropped += raw.getRawDataLen();
                continue;
            }
        }

        // Ethernet
        if(!pkt.isPacketOfType(Ethernet))
        {
            dropped++;
            bytesDropped += raw.getRawDataLen();
            continue;
        }

        // IP version filter
        if(cfg.ipVersion >= 0 && ((cfg.ipVersion == 4 && !pkt.isPacketOfType(IPv4)) ||
            (cfg.ipVersion == 6 && !pkt.isPacketOfType(IPv6)))
        {
            dropped++;
            bytesDropped += raw.getRawDataLen();
            continue;
        }

        // TTL handling
        if(cfg.ttlDec >= 0 && auto *ip4 = pkt.getLayerOfType<IPv4Layer>())
        {
            if(ip4->getIPv4Header()->timeToLive <= cfg.ttlDec || ip4->getIPv4Header()->protocol == pcpp::PACKETPP_IPPROTO_ICMP)
            {
                dropped++;
                bytesDropped += raw.getRawDataLen();
                continue;
            }
            ip4->getIPv4Header()->timeToLive -= cfg.ttlDec;
        }
        else if(cfg.ttlDec >= 0 && auto *ip6 = pkt.getLayerOfType<IPv6Layer>())
        {
            if(ip6->getIPv6Header()->hopLimit <= cfg.ttlDec || ip6->getIPv6Header()->nextHeader == pcpp::PACKETPP_IPPROTO_ICMPV6)
            {
                dropped++;
                bytesDropped += raw.getRawDataLen();
                continue;
            }
            ip6->getIPv6Header()->hopLimit -= cfg.ttlDec;
        }

        // DNS modification
        if(pkt.isPacketOfType(UDP))
        {
            auto *dns = pkt.getLayerOfType<DnsLayer>();
            auto *udp = pkt.getLayerOfType<UdpLayer>();

            if(dns && udp)
            {
                if(!cfg.dnsAddr.empty())
                {
                    if(auto *ip4 = pkt.getLayerOfType<IPv4Layer>())
                    {
                        ip4->getIPv4Header()->ipDst = IPv4Address(cfg.dnsAddr).toInt();
                    }
                    else if(auto *ip6 = pkt.getLayerOfType<IPv6Layer>())
                    {
                        memcpy(ip6->getIPv6Header()->ipDst,
                            IPv6Address(cfg.dnsAddr).toBytes(), 16);
                    }
                }

                if(cfg.dnsPort > 0)
                    udp->getUdpHeader()->portDst = htons(cfg.dnsPort);

                dnsModified++;
            }
        }

        pkt.computeCalculateFields();
        writer.writePacket(raw);

        written++;
        bytesOut += raw.getRawDataLen();
    }

    cout << "Total bytes & packets processed: " << bytesIn << "&" << totalPkts << "\n";
    cout << "Total bytes & packets dropped: " << bytesDropped << "&" << dropped << "\n";
    cout << "Total bytes & packets written: " << bytesOut << "&" << written << "\n";
    cout << "DNS modified: " << dnsModified << "\n";

    return 0;
}
