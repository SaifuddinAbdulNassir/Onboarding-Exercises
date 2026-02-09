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
    ++writtenPackets;
    bytesOut += value;
}

void PcapConvertStats::recordDroppedPacket(size_t value)
{
    ++droppedPackets;
    bytesDropped += value;
}
