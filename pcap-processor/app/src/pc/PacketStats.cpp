#include "pc/PacketStats.h"

using namespace pc;

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
