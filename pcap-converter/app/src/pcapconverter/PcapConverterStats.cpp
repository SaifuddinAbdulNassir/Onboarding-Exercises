#include "pcapconverter/PcapConverterStats.h"

using namespace pcapconverter;

// Constructors & destructors

PcapConverterStats::PcapConverterStats()
{
}

PcapConverterStats::~PcapConverterStats()
{
}

// Business logic

void PcapConverterStats::recordPacketStats(uint64_t value)
{
    // Update stats for dropped packet
    ++packetCount;
    byteCount += value;
}