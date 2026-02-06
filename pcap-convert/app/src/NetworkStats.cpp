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

void NetworkStats::recordWrittenPacket(size_t value)
{
    ++writtenPackets;
    bytesOut += value;
}

void NetworkStats::recordDroppedPacket(size_t value)
{
    ++droppedPackets;
    bytesDropped += value;
}
