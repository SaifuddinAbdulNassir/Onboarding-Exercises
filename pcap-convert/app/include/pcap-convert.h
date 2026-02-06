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
#include "NetworkStats.h"
#include "PcapConvertParams.h"

namespace pcapconvert
{

    class PcapConvert
    {
    public:
        // Constructors & destructors
        PcapConvert();
        virtual ~PcapConvert();

        // Business logic
        void applyPacketModifications(pcpp::Packet &packet, const PcapConvertParams &params, NetworkStats &stats);
        void decrementTtl(pcpp::Packet &packet, const PcapConvertParams &params);
        bool isExpiredOrIcmp(pcpp::Packet &packet, const PcapConvertParams &params);
        void modifyDnsDestination(pcpp::Packet &packet, pcpp::UdpLayer *udp, const PcapConvertParams &params);
        bool parseArgs(int argc, char *argv[], PcapConvertParams &params);
        void printStatistics(const NetworkStats &stats, pcpp::PcapFileReaderDevice &reader);
        void processPackets(pcpp::PcapFileReaderDevice &reader, pcpp::PcapFileWriterDevice &writer, const PcapConvertParams &params);
        bool shouldDropPacket(pcpp::Packet &packet, const PcapConvertParams &params);
    };

} // namespace pcapconvert