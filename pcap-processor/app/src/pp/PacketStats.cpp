#include "pp/PacketStats.h"

using namespace pp;

PacketStats::PacketStats()
{
}

PacketStats::~PacketStats()
{
}

// Business logic

void PacketStats::incrementPacketAndByteCounts(uint64_t bytes)
{
    ++packetCount;
    byteCount += bytes;
}
