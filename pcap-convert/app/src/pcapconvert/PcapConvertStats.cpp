#include "pcapconvert/PcapConvertStats.h"

using namespace pcapconvert;

// Constructors & destructors

PcapConvertStats::PcapConvertStats()
{
}

PcapConvertStats::~PcapConvertStats()
{
}

// Business logic

void PcapConvertStats::recordWrittenPacket(size_t value)
{
    // Update stats for written packet
    ++writtenPackets;
    bytesOut += value;
}

void PcapConvertStats::recordDroppedPacket(size_t value)
{
    // Update stats for dropped packet
    ++droppedPackets;
    bytesDropped += value;
}
