#pragma once

// Library includes
#include <pcapplusplus/DnsLayer.h>
#include <pcapplusplus/EthLayer.h>
#include <pcapplusplus/IPv4Layer.h>
#include <pcapplusplus/IPv6Layer.h>
#include <pcapplusplus/Packet.h>
#include <pcapplusplus/PcapFileDevice.h>
#include <pcapplusplus/UdpLayer.h>
#include <pcapplusplus/VlanLayer.h>

// Project includes
#include "PcapConvertParams.h"
#include "PcapConvertStats.h"

namespace pcapconvert
{

    class PcapConvert
    {
    private:
        // Data
        PcapConvertParams params;
        PcapConvertStats stats;

    public:
        // Constructors & destructors
        PcapConvert();
        virtual ~PcapConvert();

        // Business logic
        void applyPacketModifications(pcpp::Packet &packet);
        void decrementTtl(pcpp::Packet &packet);
        bool isExpiredOrIcmp(pcpp::Packet &packet) const;
        void modifyDnsDestination(pcpp::Packet &packet, pcpp::UdpLayer *udp);
        bool parseArgs(int argc, char *argv[]);
        void printStatistics(pcpp::PcapFileReaderDevice &reader) const;
        void processPackets();
        bool shouldDropPacket(pcpp::Packet &packet) const;
    };

} // namespace pcapconvert
