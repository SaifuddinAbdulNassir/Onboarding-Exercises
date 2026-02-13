#pragma once

// Project includes
#include "PcapConvertParams.h"
#include "PcapConvertStats.h"

namespace pcpp
{
    class Packet;
    class PcapFileReaderDevice;
    class UdpLayer;
}

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
        bool isExpiredOrIcmp(const pcpp::Packet &packet) const;
        void modifyDnsDestination(pcpp::Packet &packet, pcpp::UdpLayer *udp);
        bool parseArgs(int argc, char *argv[]);
        void printStats(const pcpp::PcapFileReaderDevice &reader) const;
        void processPackets();
        bool shouldDropPacket(const pcpp::Packet &packet) const;
    };

} // namespace pcapconvert
