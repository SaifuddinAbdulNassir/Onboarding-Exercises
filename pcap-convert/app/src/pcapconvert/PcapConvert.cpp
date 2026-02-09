#include "pcapconvert/PcapConvert.h"

// Standard includes
#include <iostream>

// Library includes
#include <cxxopts/cxxopts.hpp>
#include <libfort/fort.hpp>
#include <pcapplusplus/DnsLayer.h>
#include <pcapplusplus/EthLayer.h>
#include <pcapplusplus/IPv4Layer.h>
#include <pcapplusplus/IPv6Layer.h>
#include <pcapplusplus/VlanLayer.h>

using namespace cxxopts;
using namespace fort;
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

void PcapConvert::applyPacketModifications(Packet &packet)
{
    decrementTtl(packet);

    // Only modify DNS packets
    if (packet.isPacketOfType(UDP))
    {
        auto dns = packet.getLayerOfType<DnsLayer>();
        auto udp = packet.getLayerOfType<UdpLayer>();

        if (dns && udp)
        {
            modifyDnsDestination(packet, udp);
            stats.incrementDnsModifiedPackets();
        }
    }
}

void PcapConvert::decrementTtl(Packet &packet)
{
    // If TTL decrement is not set, skip
    if (params.getTtlDec() == nullptr)
        return;

    // Decrement TTL for both IPv4 and IPv6
    if (auto ip4 = packet.getLayerOfType<IPv4Layer>())
    {
        ip4->getIPv4Header()->timeToLive -= *params.getTtlDec();
    }
    else if (auto ip6 = packet.getLayerOfType<IPv6Layer>())
    {
        ip6->getIPv6Header()->hopLimit -= *params.getTtlDec();
    }
}

bool PcapConvert::isExpiredOrIcmp(const Packet &packet) const
{
    // If TTL decrement is not set, skip
    if (params.getTtlDec() == nullptr)
        return false;

    // Check IPv4 TTL and ICMP
    auto ip4 = packet.getLayerOfType<IPv4Layer>();
    if (ip4)
    {
        // Drop if TTL is too low to decrement OR if it's ICMP
        return (ip4->getIPv4Header()->timeToLive <= *params.getTtlDec() ||
                ip4->getIPv4Header()->protocol == PACKETPP_IPPROTO_ICMP);
    }

    // Check IPv6 Hop Limit and ICMPv6
    auto ip6 = packet.getLayerOfType<IPv6Layer>();
    if (ip6)
    {
        // Drop if Hop Limit is too low to decrement OR if it's ICMPv6
        return (ip6->getIPv6Header()->hopLimit <= *params.getTtlDec() ||
                ip6->getIPv6Header()->nextHeader == PACKETPP_IPPROTO_ICMPV6);
    }

    return false;
}

void PcapConvert::modifyDnsDestination(Packet &packet, UdpLayer *udp)
{
    // Modify destination IP if specified
    auto ip4 = packet.getLayerOfType<IPv4Layer>();
    auto ip6 = packet.getLayerOfType<IPv6Layer>();
    if (ip4 && params.getDnsV4Addr() != nullptr)
    {
        ip4->setDstIPv4Address(*params.getDnsV4Addr());
    }
    else if (ip6 && params.getDnsV6Addr() != nullptr)
    {
        ip6->setDstIPv6Address(*params.getDnsV6Addr());
    }

    // Modify destination port if specified
    if (params.getDnsPort() != nullptr)
    {
        udp->getUdpHeader()->portDst = *params.getDnsPort();
    }
}

bool PcapConvert::parseArgs(int argc, char *argv[])
{
    // Define command line options
    Options options("pcap-convert", "PCAP file converter");

    options.add_options()("v,vlan", "VLAN ID to filter on", value<uint16_t>())("ip-version", "IP version to filter on (4 or 6)", value<int>())("t,ttl", "TTL decrement value", value<uint8_t>())("dns-addr", "DNS destination address to modify to", value<string>())("dns-port", "DNS destination port to modify to", value<uint16_t>())("i,input", "Input pcap file path", value<string>())("o,output", "Output pcap file path", value<string>())("h,help", "Command to run the App: ./build/pcap-convert --vlan <vlan id> --ip-version <4|6> --ttl <decrement> --dns-addr <address> --dns-port <port> -i data/captures/<input pcap file> -o data/captures/<output pcap file>");

    // Parse options
    auto result = options.parse(argc, argv);
    if (result.count("help"))
    {
        cout << options.help() << endl;
        return false;
    }
    if (!result.count("input") || !result.count("output"))
    {
        cerr << "Input and output file paths are required.\n";
        cout << options.help() << endl;
        return false;
    }

    // Set parameters based on parsed options
    if (result.count("vlan"))
        params.setVlan(make_shared<uint16_t>(result["vlan"].as<uint16_t>()));
    if (result.count("ip-version"))
    {
        int version = result["ip-version"].as<int>();
        if (version == 4)
            params.setIpVersion(make_shared<IPAddress::AddressType>(IPAddress::IPv4AddressType));
        else if (version == 6)
            params.setIpVersion(make_shared<IPAddress::AddressType>(IPAddress::IPv6AddressType));
        else
        {
            cerr << "Invalid IP version. Use 4 or 6.\n";
            return false;
        }
    }
    if (result.count("ttl"))
        params.setTtlDec(make_shared<uint8_t>(result["ttl"].as<uint8_t>()));
    if (result.count("dns-addr"))
    {
        if (IPv4Address::isValidIPv4Address(result["dns-addr"].as<string>()))
        {
            params.setDnsV4Addr(make_shared<IPv4Address>(result["dns-addr"].as<string>()));
        }
        else
        {
            params.setDnsV6Addr(make_shared<IPv6Address>(result["dns-addr"].as<string>()));
        }
    }
    if (result.count("dns-port"))
        params.setDnsPort(make_shared<uint16_t>(result["dns-port"].as<uint16_t>()));
    if (result.count("input"))
        params.setInputFile(result["input"].as<string>());
    if (result.count("output"))
        params.setOutputFile(result["output"].as<string>());

    return true;
}

void PcapConvert::printStats(const PcapFileReaderDevice &reader) const
{
    // Get reader stats
    IPcapDevice::PcapStats readerStats;
    reader.getStatistics(readerStats);

    // Print stats in a table format
    char_table table;
    table << header << "Packet Processing Statistics" << "Total bytes" << "Total packets" << endr
          << "Total bytes & packets processed: " << stats.getBytesIn() << readerStats.packetsRecv << endr
          << "Total bytes & packets dropped:   " << stats.getBytesDropped() << stats.getDroppedPackets() << endr
          << "Total bytes & packets written:   " << stats.getBytesOut() << stats.getWrittenPackets() << endr
          << "Total DNS packets modified:      " << " " << stats.getDnsModifiedPackets() << endr;

    cout << table.to_string() << endl;
}

void PcapConvert::processPackets()
{
    // Open reader and writer devices
    PcapFileReaderDevice reader(params.getInputFile());
    if (!reader.open())
    {
        cerr << "Cannot open input file\n";
        return;
    }

    PcapFileWriterDevice writer(params.getOutputFile(), reader.getLinkLayerType());
    if (!writer.open())
    {
        cerr << "Cannot open output file\n";
        return;
    }

    RawPacket rawPacket;

    while (reader.getNextPacket(rawPacket))
    {
        stats.incrementBytesIn(rawPacket.getRawDataLen());
        Packet packet(&rawPacket);

        // Filtering
        if (shouldDropPacket(packet))
        {
            stats.recordDroppedPacket(rawPacket.getRawDataLen());
            continue;
        }

        // Modification
        applyPacketModifications(packet);

        // Finalize and Save
        packet.computeCalculateFields();
        writer.writePacket(rawPacket);
        stats.recordWrittenPacket(rawPacket.getRawDataLen());
    }
    printStats(reader);
}

bool PcapConvert::shouldDropPacket(const Packet &packet) const
{
    // 1. VLAN Filter
    if (params.getVlan() != nullptr)
    {
        auto vlan = packet.getLayerOfType<VlanLayer>();
        if (!vlan || vlan->getVlanID() != *params.getVlan())
            return true;
    }

    // 2. Ethernet Filter
    if (!packet.isPacketOfType(Ethernet))
        return true;

    // 3. IP Version Filter
    if (params.getIpVersion() != nullptr)
    {
        bool isV4 = packet.isPacketOfType(IPv4);
        bool isV6 = packet.isPacketOfType(IPv6);
        if (*params.getIpVersion() == IPAddress::IPv4AddressType && !isV4)
            return true;
        if (*params.getIpVersion() == IPAddress::IPv6AddressType && !isV6)
            return true;
    }

    // 4. TTL/Hop Limit Logic
    return isExpiredOrIcmp(packet);
}
