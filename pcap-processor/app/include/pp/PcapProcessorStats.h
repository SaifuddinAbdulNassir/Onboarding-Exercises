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
    PacketStats &getDnsModifiedPacketsStats() { return dnsModifiedPackets; }
    PacketStats &getDroppedPacketsStats() { return droppedPackets; }
    PacketStats &getIncomingPacketsStats() { return incomingPackets; }
    PacketStats &getWrittenPacketsStats() { return writtenPackets; }
  };

} // namespace pp
