#pragma once

// Project includes
#include "ndpi/NdpiConnectionsMap.h"

namespace pcpp
{
    // Forward declarations
    class RawPacket;
    class PcapLiveDevice;
}

namespace ndpi
{

    class NdpiProcessor
    {
    private:
        // Data
        std::string interface;
        size_t maxPackets = 100;

        // Helper functions
        void canonicalize(uint32_t &srcIp, uint32_t &dstIp, uint16_t &srcPort, uint16_t &dstPort);

    public:
        // Constructors & destructors
        NdpiProcessor();
        virtual ~NdpiProcessor();

        // Business logic
        void onPacketArrives(pcpp::RawPacket *rawPacket, pcpp::PcapLiveDevice *dev, void *userData);
        bool ParseArgs(int argc, char *argv[]);
        void printResults(const NdpiConnectionsMap &connectionMap) const;
        void processLivePackets();
    };

} // namespace ndpi
