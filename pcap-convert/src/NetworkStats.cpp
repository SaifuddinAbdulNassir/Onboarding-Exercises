#include "NetworkStats.h"

using namespace pcapconvert;

// Constructor and Destructor

NetworkStats::NetworkStats()
{
}

NetworkStats::~NetworkStats()
{
}

// Stats updates

void NetworkStats::incrementDroppedPackets()
{
    droppedPackets++;
}

void NetworkStats::incrementWrittenPackets()
{
    writtenPackets++;
}

void NetworkStats::addBytesIn(size_t bytes)
{
    bytesIn += bytes;
}

void NetworkStats::addBytesOut(size_t bytes)
{
    bytesOut += bytes;
}

void NetworkStats::addBytesDropped(size_t bytes)
{
    bytesDropped += bytes;
}

void NetworkStats::incrementDnsModifiedPackets()
{
    dnsModifiedPackets++;
}
