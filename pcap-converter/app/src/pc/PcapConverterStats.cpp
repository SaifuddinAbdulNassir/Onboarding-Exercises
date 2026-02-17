#include "pc/PcapConverterStats.h"

using namespace pc;

// Constructors & destructors

PcapConverterStats::PcapConverterStats()
{
}

PcapConverterStats::~PcapConverterStats()
{
}

// Business logic

void PcapConverterStats::incrementPacketAndByteCounts(uint64_t value)
{
    // Update stats for dropped packet
    ++packetCount;
    byteCount += value;
}
