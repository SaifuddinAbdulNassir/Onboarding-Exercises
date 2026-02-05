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
#include "Config.h"
#include "NetworkStats.h"

namespace pcapconvert
{

    class PcapConvert
    {
    public:
        // Constructors & destructors
        PcapConvert();
        virtual ~PcapConvert();

        // Business logic
        void applyPacketModifications(pcpp::Packet &packet, const Config &config, NetworkStats &stats);
        void decrementTtl(pcpp::Packet &packet, const Config &config);
        bool isExpiredOrIcmp(pcpp::Packet &packet, const Config &config);
        void modifyDnsDestination(pcpp::Packet &packet, pcpp::UdpLayer *udp, const Config &config);
        bool parseArgs(int argc, char *argv[], Config &config);
        void printStatistics(const NetworkStats &stats, pcpp::PcapFileReaderDevice &reader);
        void processPackets(pcpp::PcapFileReaderDevice &reader, pcpp::PcapFileWriterDevice &writer, const Config &config);
        bool shouldDropPacket(pcpp::Packet &packet, const Config &config);
    };

} // namespace pcapconvert