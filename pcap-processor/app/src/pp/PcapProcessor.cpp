#include "pp/PcapProcessor.h"

// Standard includes
#include <iostream>

// Library includes
#include <libfort/fort.hpp>
#include <pcapplusplus/DnsLayer.h>
#include <pcapplusplus/EthLayer.h>
#include <pcapplusplus/IPv4Layer.h>
#include <pcapplusplus/IPv6Layer.h>
#include <pcapplusplus/Packet.h>
#include <pcapplusplus/PcapFileDevice.h>
#include <pcapplusplus/UdpLayer.h>
#include <pcapplusplus/VlanLayer.h>

using namespace fort;
using namespace pp;
using namespace pcpp;
using namespace std;

// Constructors & destructors

PcapProcessor::PcapProcessor()
{
}

PcapProcessor::~PcapProcessor()
{
}

// Helpers

void PcapProcessor::applyPacketModifications(Packet &packet)
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
            stats.incrementDnsModified(packet.getRawPacket()->getRawDataLen());
        }
    }
}

void PcapProcessor::decrementTtl(Packet &packet)
{
    // If TTL decrement is not set, skip
    if (!params.getTtlDec())
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

bool PcapProcessor::isExpiredOrIcmp(const Packet &packet) const
{
    // If TTL decrement is not set, skip
    if (!params.getTtlDec())
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

void PcapProcessor::modifyDnsDestination(Packet &packet, UdpLayer *udp)
{
    // Modify destination IP if specified
    auto ip4 = packet.getLayerOfType<IPv4Layer>();
    auto ip6 = packet.getLayerOfType<IPv6Layer>();
    auto dnsAddress = params.getDnsAddress();
    if (dnsAddress)
    {
        if (ip4 && dnsAddress->isIPv4())
        {
            ip4->setDstIPv4Address(dnsAddress->getIPv4());
        }
        else if (ip6 && dnsAddress->isIPv6())
        {
            ip6->setDstIPv6Address(dnsAddress->getIPv6());
        }
    }

    // Modify destination port if specified
    if (params.getDnsPort())
    {
        udp->getUdpHeader()->portDst = *params.getDnsPort();
    }
}

void PcapProcessor::printStats()
{
    // Print stats in a table format
    char_table table;
    table << header << "Packet Processing Statistics" << "Total bytes" << "Total packets" << endr
          << "Total bytes & packets processed: " << stats.getIncomingByteCount() << stats.getIncomingPacketCount() << endr
          << "Total bytes & packets dropped:   " << stats.getDroppedByteCount() << stats.getDroppedPacketCount() << endr
          << "Total bytes & packets written:   " << stats.getWrittenByteCount() << stats.getWrittenPacketCount() << endr
          << "Total DNS packets modified:      " << stats.getDnsModifiedByteCount() << stats.getDnsModifiedPacketCount() << endr;

    cout << table.to_string() << endl;
}

bool PcapProcessor::shouldDropPacket(const Packet &packet) const
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

// Business logic

PcapProcessor PcapProcessor::create(int argc, char *argv[])
{
    PcapProcessor processor;
    processor.params = PcapProcessorParams::create(argc, argv);
    return processor;
}

void PcapProcessor::processPackets()
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
        stats.incrementIncoming(rawPacket.getRawDataLen());
        Packet packet(&rawPacket);

        // Filtering
        if (shouldDropPacket(packet))
        {
            stats.incrementDropped(rawPacket.getRawDataLen());
            continue;
        }

        // Modification
        applyPacketModifications(packet);

        // Finalize and Save
        packet.computeCalculateFields();
        writer.writePacket(rawPacket);
        stats.incrementWritten(rawPacket.getRawDataLen());
    }
    printStats();
}
