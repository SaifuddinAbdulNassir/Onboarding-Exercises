#include "pcap-convert.h"

// Standard includes
#include <iostream>

using namespace pcapconvert;
using namespace pcpp;
using namespace std;

// Constructors & destructors

PcapConvert::PcapConvert()
{
}

PcapConvert::~PcapConvert()
{
}

// Business logic

void PcapConvert::applyPacketModifications(Packet &packet, const Config &config, NetworkStats &stats)
{
    decrementTtl(packet, config);

    if (packet.isPacketOfType(UDP))
    {
        auto dns = packet.getLayerOfType<DnsLayer>();
        auto udp = packet.getLayerOfType<UdpLayer>();

        if (dns && udp)
        {
            modifyDnsDestination(packet, udp, config);
            stats.incrementDnsModifiedPackets();
        }
    }
}

void PcapConvert::decrementTtl(Packet &packet, const Config &config)
{
    if (config.getTtlDec() <= 0)
        return;

    if (auto ip4 = packet.getLayerOfType<IPv4Layer>())
    {
        ip4->getIPv4Header()->timeToLive -= config.getTtlDec();
    }
    else if (auto ip6 = packet.getLayerOfType<IPv6Layer>())
    {
        ip6->getIPv6Header()->hopLimit -= config.getTtlDec();
    }
}

bool PcapConvert::isExpiredOrIcmp(Packet &packet, const Config &config)
{
    if (config.getTtlDec() < 0)
        return false;

    auto ip4 = packet.getLayerOfType<IPv4Layer>();
    if (ip4)
    {
        // Drop if TTL is too low to decrement OR if it's ICMP
        return (ip4->getIPv4Header()->timeToLive <= config.getTtlDec() ||
                ip4->getIPv4Header()->protocol == PACKETPP_IPPROTO_ICMP);
    }

    auto ip6 = packet.getLayerOfType<IPv6Layer>();
    if (ip6)
    {
        // Drop if Hop Limit is too low to decrement OR if it's ICMPv6
        return (ip6->getIPv6Header()->hopLimit <= config.getTtlDec() ||
                ip6->getIPv6Header()->nextHeader == PACKETPP_IPPROTO_ICMPV6);
    }

    return false;
}

void PcapConvert::modifyDnsDestination(Packet &packet, UdpLayer *udp, const Config &config)
{
    if (!config.getDnsAddr().empty())
    {
        if (auto ip4 = packet.getLayerOfType<IPv4Layer>())
        {
            ip4->getIPv4Header()->ipDst = IPv4Address(config.getDnsAddr()).toInt();
        }
        else if (auto ip6 = packet.getLayerOfType<IPv6Layer>())
        {
            memcpy(ip6->getIPv6Header()->ipDst, IPv6Address(config.getDnsAddr()).toBytes(), 16);
        }
    }
    if (config.getDnsPort() > 0)
    {
        udp->getUdpHeader()->portDst = config.getDnsPort();
    }
}

bool PcapConvert::parseArgs(int argc, char *argv[], Config &config)
{
    for (int i = 1; i < argc; ++i)
    {
        string arg = argv[i];

        if (arg == "--vlan" && i + 1 < argc)
            config.setVlan(stoi(argv[++i]));
        else if (arg == "-ip-version" && i + 1 < argc)
            config.setIpVersion(stoi(argv[++i]));
        else if (arg == "--ttl" && i + 1 < argc)
            config.setTtlDec(stoi(argv[++i]));
        else if (arg == "--dns-addr" && i + 1 < argc)
            config.setDnsAddr(argv[++i]);
        else if (arg == "--dns-port" && i + 1 < argc)
            config.setDnsPort(stoi(argv[++i]));
        else if (arg == "-i" && i + 1 < argc)
            config.setInputFile(argv[++i]);
        else if (arg == "-o" && i + 1 < argc)
            config.setOutputFile(argv[++i]);
        else if (arg == "-h" || arg == "--help")
        {
            cout << "Command to run the App: ./build/pcap-convert [--vlan <vlan id>] [-ip-version <4|6>] [--ttl <decrement>] " << "[--dns-addr <address>] [--dns-port <port>]  -i data/captures/<input pcap file> -o data/captures/<output pcap file>  \n";
        }
    }

    return !config.getInputFile().empty() && !config.getOutputFile().empty();
}

void PcapConvert::printStatistics(const NetworkStats &stats, PcapFileReaderDevice &reader)
{
    IPcapDevice::PcapStats readerStats;
    reader.getStatistics(readerStats);

    cout << "\n=== Packet Processing Statistics ===\n";
    cout << "Total bytes & packets processed: " << stats.getBytesIn()
         << " & " << readerStats.packetsRecv << "\n";

    cout << "Total bytes & packets dropped:   " << stats.getBytesDropped()
         << " & " << stats.getDroppedPackets() << "\n";

    cout << "Total bytes & packets written:   " << stats.getBytesOut()
         << " & " << stats.getWrittenPackets() << "\n";

    cout << "Total DNS packets modified:      " << stats.getDnsModifiedPackets() << "\n";
    cout << "====================================\n";
}

void PcapConvert::processPackets(PcapFileReaderDevice &reader, PcapFileWriterDevice &writer, const Config &config)
{
    RawPacket rawPacket;
    NetworkStats stats;

    while (reader.getNextPacket(rawPacket))
    {
        stats.addBytesIn(rawPacket.getRawDataLen());
        Packet packet(&rawPacket);

        // Filtering
        if (shouldDropPacket(packet, config))
        {
            stats.incrementDroppedPackets();
            stats.addBytesDropped(rawPacket.getRawDataLen());
            continue;
        }

        // Modification
        applyPacketModifications(packet, config, stats);

        // Finalize and Save
        packet.computeCalculateFields();
        writer.writePacket(rawPacket);
        stats.incrementWrittenPackets();
        stats.addBytesOut(rawPacket.getRawDataLen());
    }
    printStatistics(stats, reader);
}

bool PcapConvert::shouldDropPacket(Packet &packet, const Config &config)
{
    // 1. VLAN Filter
    if (config.getVlan() >= 0)
    {
        auto vlan = packet.getLayerOfType<VlanLayer>();
        if (!vlan || vlan->getVlanID() != config.getVlan())
            return true;
    }

    // 2. Ethernet Filter
    if (!packet.isPacketOfType(Ethernet))
        return true;

    // 3. IP Version Filter
    if (config.getIpVersion() >= 0)
    {
        bool isV4 = packet.isPacketOfType(IPv4);
        bool isV6 = packet.isPacketOfType(IPv6);
        if (config.getIpVersion() == 4 && !isV4)
            return true;
        if (config.getIpVersion() == 6 && !isV6)
            return true;
    }

    // 4. TTL/Hop Limit Logic
    return isExpiredOrIcmp(packet, config);
}
