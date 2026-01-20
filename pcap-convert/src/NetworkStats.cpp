#include "NetworkStats.h"

void NetworkStats::incrementTotalPackets()
{
    totalPackets++;
}

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

int NetworkStats::getTotalPackets() const
{
    return totalPackets;
}

int NetworkStats::getDroppedPackets() const
{
    return droppedPackets;
}

int NetworkStats::getWrittenPackets() const
{
    return writtenPackets;
}

size_t NetworkStats::getBytesIn() const
{
    return bytesIn;
}

size_t NetworkStats::getBytesOut() const
{
    return bytesOut;
}

size_t NetworkStats::getBytesDropped() const
{
    return bytesDropped;
}

int NetworkStats::getDnsModifiedPackets() const
{
    return dnsModifiedPackets;
}
