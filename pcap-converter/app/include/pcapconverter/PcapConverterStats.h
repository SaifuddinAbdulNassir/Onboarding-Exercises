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
    uint64_t bytesDropped = 0;
    uint64_t bytesIn = 0;
    uint64_t bytesOut = 0;
    size_t dnsModifiedPackets = 0;
    size_t droppedPackets = 0;
    size_t writtenPackets = 0;

  public:
    // Constructors & destructors
    PcapConverterStats();
    virtual ~PcapConverterStats();

    // Getters & setters
    uint64_t getBytesDropped() const { return bytesDropped; }
    uint64_t getBytesIn() const { return bytesIn; }
    uint64_t getBytesOut() const { return bytesOut; }
    size_t getDnsModifiedPackets() const { return dnsModifiedPackets; }
    size_t getDroppedPackets() const { return droppedPackets; }
    size_t getWrittenPackets() const { return writtenPackets; }

    // Business logic
    void incrementBytesIn(uint64_t value) { bytesIn += value; };
    void incrementDnsModifiedPackets() { ++dnsModifiedPackets; };
    void recordDroppedPacket(uint64_t value);
    void recordWrittenPacket(uint64_t value);
  };

} // namespace pcapconvert
