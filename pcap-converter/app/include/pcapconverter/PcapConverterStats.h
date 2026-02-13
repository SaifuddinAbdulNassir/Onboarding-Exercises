#pragma once

// Standard includes
#include <cstddef>
#include <cstdint>

namespace pcapconverter
{

  class PcapConverterStats
  {
  private:
    // Data
    uint64_t bytesDroppedCount = 0;
    uint64_t bytesInCount = 0;
    uint64_t bytesOutCount = 0;
    size_t packetsDnsModifiedCount = 0;
    size_t packetsDroppedCount = 0;
    size_t packetWrittenCount = 0;

  public:
    // Constructors & destructors
    PcapConverterStats();
    virtual ~PcapConverterStats();

    // Getters & setters
    uint64_t getBytesDroppedCount() const { return bytesDroppedCount; }
    uint64_t getBytesInCount() const { return bytesInCount; }
    uint64_t getBytesOutCount() const { return bytesOutCount; }
    size_t getPacketsDnsModifiedCount() const { return packetsDnsModifiedCount; }
    size_t getPacketsDroppedCount() const { return packetsDroppedCount; }
    size_t getPacketWrittenCount() const { return packetWrittenCount; }

    // Business logic
    void incrementBytesInCount(uint64_t value) { bytesInCount += value; };
    void incrementPacketsDnsModifiedCount() { ++packetsDnsModifiedCount; };
    void recordDroppedPacket(uint64_t value);
    void recordWrittenPacket(uint64_t value);
  };

} // namespace pcapconverter
