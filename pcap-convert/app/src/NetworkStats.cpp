#include "NetworkStats.h"

using namespace pcapconvert;

// Constructors & destructors

NetworkStats::NetworkStats()
{
}

NetworkStats::~NetworkStats()
{
}

// Business logic

void NetworkStats::recordWrittenPacket(uint32_t value)
{
    ++writtenPackets;
    bytesOut += value;
}

void NetworkStats::recordDroppedPacket(uint32_t value)
{
    ++droppedPackets;
    bytesDropped += value;
}
