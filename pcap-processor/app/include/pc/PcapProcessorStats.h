#pragma once

// Standard includes
#include <cstddef>
#include <cstdint>

namespace pc
{

  class PcapProcessorStats
  {
  private:
    // Data
    uint64_t byteCount = 0;
    size_t packetCount = 0;

  public:
    // Constructors & destructors
    PcapProcessorStats();
    virtual ~PcapProcessorStats();

    // Getters & setters
    uint64_t getByteCount() const { return byteCount; }
    size_t getPacketCount() const { return packetCount; }

    // Business logic
    void incrementPacketAndByteCounts(uint64_t bytes);
  };

} // namespace pc
