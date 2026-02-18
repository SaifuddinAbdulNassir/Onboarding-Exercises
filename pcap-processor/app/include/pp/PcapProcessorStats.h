#pragma once

// Project includes
#include "pp/PacketStats.h"

namespace pp
{

  class PcapProcessorStats
  {
  private:
    // Data
    PacketStats dnsModifiedPackets;
    PacketStats droppedPackets;
    PacketStats incomingPackets;
    PacketStats writtenPackets;

  public:
    // Constructors & destructors
    PcapProcessorStats();
    virtual ~PcapProcessorStats();

    // Getters and setters
    size_t getDnsModifiedByteCount() const { return dnsModifiedPackets.getByteCount(); }
    uint64_t getDnsModifiedPacketCount() const { return dnsModifiedPackets.getPacketCount(); }
    size_t getDroppedByteCount() const { return droppedPackets.getByteCount(); }
    uint64_t getDroppedPacketCount() const { return droppedPackets.getPacketCount(); }
    size_t getIncomingByteCount() const { return incomingPackets.getByteCount(); }
    uint64_t getIncomingPacketCount() const { return incomingPackets.getPacketCount(); }
    size_t getWrittenByteCount() const { return writtenPackets.getByteCount(); }
    uint64_t getWrittenPacketCount() const { return writtenPackets.getPacketCount(); }

    // Business logic
    void incrementDnsModified(uint64_t bytes) { dnsModifiedPackets.increment(bytes); }
    void incrementDropped(uint64_t bytes) { droppedPackets.increment(bytes); }
    void incrementIncoming(uint64_t bytes) { incomingPackets.increment(bytes); }
    void incrementWritten(uint64_t bytes) { writtenPackets.increment(bytes); }
  };

} // namespace pp
