#include "pc/PcapProcessorStats.h"

using namespace pc;

// Constructors & destructors

PcapProcessorStats::PcapProcessorStats()
{
}

PcapProcessorStats::~PcapProcessorStats()
{
}

// Business logic

void PcapProcessorStats::incrementPacketAndByteCounts(uint64_t value)
{
    // Update stats for dropped packet
    ++packetCount;
    byteCount += value;
}
