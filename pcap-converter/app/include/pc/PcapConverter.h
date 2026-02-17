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

        // Helpers
        void applyPacketModifications(pcpp::Packet &packet);
        void decrementTtl(pcpp::Packet &packet);
        bool isExpiredOrIcmp(const pcpp::Packet &packet) const;
        void modifyDnsDestination(pcpp::Packet &packet, pcpp::UdpLayer *udp);
        void printStats() const;
        bool shouldDropPacket(const pcpp::Packet &packet) const;

    public:
        // Constructors & destructors
        PcapConverter();
        virtual ~PcapConverter();

        // Business logic
        bool parseArgs(int argc, char *argv[]);
        void processPackets();
    };

} // namespace pc
