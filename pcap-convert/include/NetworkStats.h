#pragma once

#include <cstddef>

namespace pcapconvert
{

  class NetworkStats
  {  
    private:
      // Data
      int totalPackets = 0;
      int droppedPackets = 0;
      int writtenPackets = 0;
      size_t bytesIn = 0;
      size_t bytesOut = 0;
      size_t bytesDropped = 0;
      int dnsModifiedPackets = 0;

    public:
      // Constructor and Destructor
      NetworkStats();
      ~NetworkStats();
  
      // Stats updates
      void addBytesDropped(size_t bytes);
      void addBytesIn(size_t bytes);
      void addBytesOut(size_t bytes);
      void incrementDnsModifiedPackets();
      void incrementDroppedPackets();
      void incrementTotalPackets();
      void incrementWrittenPackets();
      
      // Getters
      size_t getBytesDropped() const { return bytesDropped; }
      size_t getBytesIn() const { return bytesIn; }
      size_t getBytesOut() const { return bytesOut; }
      int getDnsModifiedPackets() const { return dnsModifiedPackets; }
      int getDroppedPackets() const { return droppedPackets; }
      int getTotalPackets() const { return totalPackets; }
      int getWrittenPackets() const { return writtenPackets; }
  };

} // namespace pcapconvert
