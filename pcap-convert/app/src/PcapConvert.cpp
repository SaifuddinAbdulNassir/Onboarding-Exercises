#include "PcapConvert.h"

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
    if (params.getTtlDec() == nullptr)
        return;

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
    if (params.getTtlDec() == nullptr)
        return false;

    auto ip4 = packet.getLayerOfType<IPv4Layer>();
    if (ip4)
    {
        // Drop if TTL is too low to decrement OR if it's ICMP
        return (ip4->getIPv4Header()->timeToLive <= *params.getTtlDec() ||
                ip4->getIPv4Header()->protocol == PACKETPP_IPPROTO_ICMP);
    }

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

    if (params.getDnsPort() != nullptr)
    {
        udp->getUdpHeader()->portDst = *params.getDnsPort();
    }
}

bool PcapConvert::parseArgs(int argc, char *argv[])
{
    cxxopts::Options options("pcap-convert", "PCAP file converter");

    options.add_options()("v,vlan", "VLAN ID to filter on", cxxopts::value<uint16_t>())("ip-version", "IP version to filter on (4 or 6)", cxxopts::value<int>())("t,ttl", "TTL decrement value", cxxopts::value<uint8_t>())("dns-addr", "DNS destination address to modify to", cxxopts::value<std::string>())("dns-port", "DNS destination port to modify to", cxxopts::value<uint16_t>())("i,input", "Input pcap file path", cxxopts::value<std::string>())("o,output", "Output pcap file path", cxxopts::value<std::string>())("h,help", "Command to run the App: ./build/pcap-convert --vlan <vlan id> --ip-version <4|6> --ttl <decrement> --dns-addr <address> --dns-port <port> -i data/captures/<input pcap file> -o data/captures/<output pcap file>");

    auto result = options.parse(argc, argv);
    if (result.count("help") || !result.count("input") || !result.count("output"))
    {
        cout << options.help() << endl;
        return false;
    }

    if (result.count("vlan"))
        params.setVlan(std::make_shared<uint16_t>(result["vlan"].as<uint16_t>()));
    if (result.count("ip-version"))
    {
        int version = result["ip-version"].as<int>();
        if (version == 4)
            params.setIpVersion(std::make_shared<pcpp::IPAddress::AddressType>(pcpp::IPAddress::IPv4AddressType));
        else if (version == 6)
            params.setIpVersion(std::make_shared<pcpp::IPAddress::AddressType>(pcpp::IPAddress::IPv6AddressType));
        else
        {
            cerr << "Invalid IP version. Use 4 or 6.\n";
            return false;
        }
    }
    if (result.count("ttl"))
        params.setTtlDec(std::make_shared<uint8_t>(result["ttl"].as<uint8_t>()));
    if (result.count("dns-addr"))
    {
        if (IPv4Address::isValidIPv4Address(result["dns-addr"].as<std::string>()))
        {
            params.setDnsV4Addr(std::make_shared<IPv4Address>(result["dns-addr"].as<std::string>()));
        }
        else
        {
            params.setDnsV6Addr(std::make_shared<IPv6Address>(result["dns-addr"].as<std::string>()));
        }
    }
    if (result.count("dns-port"))
        params.setDnsPort(std::make_shared<uint16_t>(result["dns-port"].as<uint16_t>()));
    if (result.count("input"))
        params.setInputFile(result["input"].as<string>());
    if (result.count("output"))
        params.setOutputFile(result["output"].as<string>());

    return true;
}

void PcapConvert::printStats(const PcapFileReaderDevice &reader) const
{
    IPcapDevice::PcapStats readerStats;
    reader.getStatistics(readerStats);

    fort::char_table table;
    table << fort::header << "Packet Processing Statistics" << "Total bytes" << "Total packets" << fort::endr
          << "Total bytes & packets processed: " << stats.getBytesIn() << readerStats.packetsRecv << fort::endr
          << "Total bytes & packets dropped:   " << stats.getBytesDropped() << stats.getDroppedPackets() << fort::endr
          << "Total bytes & packets written:   " << stats.getBytesOut() << stats.getWrittenPackets() << fort::endr
          << "Total DNS packets modified:      " << " " << stats.getDnsModifiedPackets() << fort::endr;

    std::cout << table.to_string() << std::endl;
}

void PcapConvert::processPackets()
{
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
        if (*params.getIpVersion() == 4 && !isV4)
            return true;
        if (*params.getIpVersion() == 6 && !isV6)
            return true;
    }

    // 4. TTL/Hop Limit Logic
    return isExpiredOrIcmp(packet);
}
