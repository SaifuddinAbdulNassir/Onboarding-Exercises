#pragma once

#include <cstddef>

class NetworkStats
{
    public:
        void incrementTotalPackets();
        void incrementDroppedPackets();
        void incrementWrittenPackets();
        void addBytesIn(size_t bytes);
        void addBytesOut(size_t bytes);
        void addBytesDropped(size_t bytes);
        void incrementDnsModifiedPackets();
    
        int getTotalPackets() const;
        int getDroppedPackets() const;
        int getWrittenPackets() const;
        size_t getBytesIn() const;
        size_t getBytesOut() const;
        size_t getBytesDropped() const;
        int getDnsModifiedPackets() const;
    
    private:
        int totalPackets = 0;
        int droppedPackets = 0;
        int writtenPackets = 0;
        size_t bytesIn = 0;
        size_t bytesOut = 0;
        size_t bytesDropped = 0;
        int dnsModifiedPackets = 0;
};