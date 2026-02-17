#pragma once

// Project includes
#include "PcapConverterParams.h"
#include "PcapConverterStats.h"

namespace pcpp
{
    // Forward declarations
    class Packet;
    class PcapFileReaderDevice;
    class UdpLayer;
}

namespace pc
{
    class PcapConverter
    {
    private:
        // Data
        PcapConverterParams params;
        PcapConverterStats dnsModifiedPacketsStats;
        PcapConverterStats droppedPacketsStats;
        PcapConverterStats incomingPacketsStats;
        PcapConverterStats writtenPacketsStats;

    public:
        // Constructors & destructors
        PcapConverter();
        virtual ~PcapConverter();

        // Business logic
        void applyPacketModifications(pcpp::Packet &packet);
        void decrementTtl(pcpp::Packet &packet);
        bool isExpiredOrIcmp(const pcpp::Packet &packet) const;
        void modifyDnsDestination(pcpp::Packet &packet, pcpp::UdpLayer *udp);
        bool parseArgs(int argc, char *argv[]);
        void printStats(const pcpp::PcapFileReaderDevice &reader) const;
        void processPackets();
        bool shouldDropPacket(const pcpp::Packet &packet) const;
    };

} // namespace pc
