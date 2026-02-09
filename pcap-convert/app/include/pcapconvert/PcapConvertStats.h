#pragma once

// Standard includes
#include <cstddef>

namespace pcapconvert
{

  class PcapConvertStats
  {
  private:
    // Data
    size_t bytesDropped = 0;
    size_t bytesIn = 0;
    size_t bytesOut = 0;
    size_t dnsModifiedPackets = 0;
    size_t droppedPackets = 0;
    size_t writtenPackets = 0;

  public:
    // Constructors & destructors
    PcapConvertStats();
    virtual ~PcapConvertStats();

    // Getters & setters
    size_t getBytesDropped() const { return bytesDropped; }
    size_t getBytesIn() const { return bytesIn; }
    size_t getBytesOut() const { return bytesOut; }
    size_t getDnsModifiedPackets() const { return dnsModifiedPackets; }
    size_t getDroppedPackets() const { return droppedPackets; }
    size_t getWrittenPackets() const { return writtenPackets; }

    // Business logic
    void incrementBytesIn(size_t value) { bytesIn += value; };
    void incrementDnsModifiedPackets() { ++dnsModifiedPackets; };
    void recordDroppedPacket(size_t value);
    void recordWrittenPacket(size_t value);
  };

} // namespace pcapconvert
