#pragma once

// Project includes
#include "pp/PcapProcessorParams.h"
#include "pp/PcapProcessorStats.h"

namespace pcpp
{
    // Forward declarations
    class Packet;
    class PcapFileReaderDevice;
    class UdpLayer;
}

namespace pp
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
        PcapProcessor();
        virtual ~PcapProcessor();

        // Business logic
        static PcapProcessor create(int argc, char *argv[]);
        void processPackets();
    };

} // namespace pp
