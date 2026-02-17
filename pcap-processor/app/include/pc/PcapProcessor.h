#pragma once

// Project includes
#include "pc/PcapProcessorParams.h"
#include "pc/PcapProcessorStats.h"

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
        PcapProcessorStats stats;

        // Helpers
        void applyPacketModifications(pcpp::Packet &packet);
        void decrementTtl(pcpp::Packet &packet);
        bool isExpiredOrIcmp(const pcpp::Packet &packet) const;
        void modifyDnsDestination(pcpp::Packet &packet, pcpp::UdpLayer *udp);
        void printStats();
        bool shouldDropPacket(const pcpp::Packet &packet) const;

    public:
        // Constructors & destructors
        PcapProcessor(int argc, char *argv[]);
        virtual ~PcapProcessor();

        // Business logic
        void processPackets();
    };

} // namespace pc
