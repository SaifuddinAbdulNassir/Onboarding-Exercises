#pragma once

// Standard includes
#include <cstddef>
#include <cstdint>

namespace pp
{

    class PacketStats
    {
    private:
        // Data
        uint64_t byteCount = 0;
        size_t packetCount = 0;

    public:
        // Constructors & destructors
        PacketStats();
        ~PacketStats();

        // Getters and setters
        uint64_t getByteCount() { return byteCount; }
        size_t getPacketCount() { return packetCount; }

        // Business logic
        void incrementPacketAndByteCounts(uint64_t bytes);
    };

} // namespace pp
