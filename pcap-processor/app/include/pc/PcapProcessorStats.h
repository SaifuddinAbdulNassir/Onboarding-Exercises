#pragma once

// Project includes
#include "pc/PacketStats.h"

namespace pc
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
    PacketStats &getDnsModifiedPacketsStats() { return dnsModifiedPackets; }
    PacketStats &getDroppedPacketsStats() { return droppedPackets; }
    PacketStats &getIncomingPacketsStats() { return incomingPackets; }
    PacketStats &getWrittenPacketsStats() { return writtenPackets; }
  };

} // namespace pc
