#pragma once

#include <cstddef>

namespace pcapconvert
{

  class NetworkStats
  {
  private:
    // Data
    int droppedPackets = 0;
    int writtenPackets = 0;
    size_t bytesIn = 0;
    size_t bytesOut = 0;
    size_t bytesDropped = 0;
    int dnsModifiedPackets = 0;

  public:
    // Constructors & destructors
    NetworkStats();
    virtual ~NetworkStats();

    // Getters & setters
    size_t getBytesDropped() const { return bytesDropped; }
    size_t getBytesIn() const { return bytesIn; }
    size_t getBytesOut() const { return bytesOut; }
    int getDnsModifiedPackets() const { return dnsModifiedPackets; }
    int getDroppedPackets() const { return droppedPackets; }
    int getWrittenPackets() const { return writtenPackets; }

    // Business logic
    void addBytesDropped(size_t bytes) { bytesDropped += bytes; };
    void addBytesIn(size_t bytes) { bytesIn += bytes; };
    void addBytesOut(size_t bytes) { bytesOut += bytes; };
    void incrementDnsModifiedPackets() { dnsModifiedPackets++; };
    void incrementDroppedPackets() { droppedPackets++; };
    void incrementWrittenPackets() { writtenPackets++; };
  };

} // namespace pcapconvert
