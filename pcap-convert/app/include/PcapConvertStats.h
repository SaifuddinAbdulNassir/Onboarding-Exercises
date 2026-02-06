#pragma once

// Standard includes
#include <cstdint>

namespace pcapconvert
{

  class PcapConvertStats
  {
  private:
    // Data
    uint32_t bytesDropped = 0;
    uint32_t bytesIn = 0;
    uint32_t bytesOut = 0;
    uint32_t dnsModifiedPackets = 0;
    uint32_t droppedPackets = 0;
    uint32_t writtenPackets = 0;

  public:
    // Constructors & destructors
    PcapConvertStats();
    virtual ~PcapConvertStats();

    // Getters & setters
    uint32_t getBytesDropped() const { return bytesDropped; }
    uint32_t getBytesIn() const { return bytesIn; }
    uint32_t getBytesOut() const { return bytesOut; }
    uint32_t getDnsModifiedPackets() const { return dnsModifiedPackets; }
    uint32_t getDroppedPackets() const { return droppedPackets; }
    uint32_t getWrittenPackets() const { return writtenPackets; }

    // Business logic
    void incrementBytesIn(uint32_t value) { bytesIn += value; };
    void incrementDnsModifiedPackets() { ++dnsModifiedPackets; };
    void recordDroppedPacket(uint32_t value);
    void recordWrittenPacket(uint32_t value);
  };

} // namespace pcapconvert
