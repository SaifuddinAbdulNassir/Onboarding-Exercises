#pragma once

// Library includes
#include <pcapplusplus/Packet.h>
#include <pcapplusplus/PcapLiveDevice.h>

// Project includes
#include "ConnectionsMap.h"

namespace ndpi
{

    class NdpiProcessor
    {
    private:
        // Data
        std::string interface;
        uint32_t maxPackets = 100;

        // Helper functions
        void canonicalize(uint32_t &srcIp, uint32_t &dstIp, uint16_t &srcPort, uint16_t &dstPort);

    public:
        // Constructors & destructors
        NdpiProcessor();
        virtual ~NdpiProcessor();

        // Business logic
        void onPacketArrives(pcpp::RawPacket *rawPacket, pcpp::PcapLiveDevice *dev, void *userData);
        bool ParseArgs(int argc, char *argv[]);
        void printResults(const ConnectionsMap &connectionMap);
        void processLivePackets();
    };

} // namespace ndpi