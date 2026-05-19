#include "pp/core/PacketStats.h"

using namespace pp;

// Constructors & destructors

PacketStats::PacketStats()
{
}

PacketStats::~PacketStats()
{
}

// Business logic

void PacketStats::increment(uint64_t bytes)
{
    ++packetCount;
    byteCount += bytes;
}
