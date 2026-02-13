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

void PcapConverterStats::recordDroppedPacket(size_t value)
{
    // Update stats for dropped packet
    ++droppedPackets;
    bytesDropped += value;
}

void PcapConverterStats::recordWrittenPacket(size_t value)
{
    // Update stats for written packet
    ++writtenPackets;
    bytesOut += value;
}
