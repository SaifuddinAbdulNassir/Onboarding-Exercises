#pragma once

// Standard includes
#include <cstddef>
#include <cstdint>

namespace pc
{

  class PcapConverterStats
  {
  private:
    // Data
    uint64_t byteCount = 0;
    size_t packetCount = 0;

  public:
    // Constructors & destructors
    PcapConverterStats();
    virtual ~PcapConverterStats();

    // Getters & setters
    uint64_t getByteCount() const { return byteCount; }
    size_t getPacketCount() const { return packetCount; }

    // Business logic
    void recordPacketStats(uint64_t value);
  };

} // namespace pc
