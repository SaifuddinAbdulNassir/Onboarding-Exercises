#include "PcapConvertStats.h"

using namespace pcapconvert;

// Constructors & destructors

PcapConvertStats::PcapConvertStats()
{
}

PcapConvertStats::~PcapConvertStats()
{
}

// Business logic

void PcapConvertStats::recordWrittenPacket(uint32_t value)
{
    ++writtenPackets;
    bytesOut += value;
}

void PcapConvertStats::recordDroppedPacket(uint32_t value)
{
    ++droppedPackets;
    bytesDropped += value;
}
