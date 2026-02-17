#pragma once

// Project includes
#include "PcapProcessorParams.h"
#include "PcapProcessorStats.h"

namespace pcpp
{
    // Forward declarations
    class Packet;
    class PcapFileReaderDevice;
    class UdpLayer;
}

namespace pc
{
    class PcapProcessor
    {
    private:
        // Data
        PcapProcessorParams params;
        PcapProcessorStats dnsModifiedPacketsStats;
        PcapProcessorStats droppedPacketsStats;
        PcapProcessorStats incomingPacketsStats;
        PcapProcessorStats writtenPacketsStats;

        // Helpers
        void applyPacketModifications(pcpp::Packet &packet);
        void decrementTtl(pcpp::Packet &packet);
        bool isExpiredOrIcmp(const pcpp::Packet &packet) const;
        void modifyDnsDestination(pcpp::Packet &packet, pcpp::UdpLayer *udp);
        void printStats() const;
        bool shouldDropPacket(const pcpp::Packet &packet) const;

    public:
        // Constructors & destructors
        PcapProcessor();
        virtual ~PcapProcessor();

        // Business logic
        bool parseArgs(int argc, char *argv[]);
        void processPackets();
    };

} // namespace pc
