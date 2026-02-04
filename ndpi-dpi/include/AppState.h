#pragma once

// Standard includes
#include <cstdint>

namespace ndpi
{

  class AppState
  {
  private:
    // Data
    uint32_t maxPackets;
    bool running;
    uint64_t uid;

    // Constants
    static const uint32_t DEFAULT_MAX_PACKETS = 100;
    static const bool DEFAULT_RUNNING = true;
    static const uint64_t DEFAULT_UID = 0;

  public:
    // Constructors & destructors
    AppState();
    virtual ~AppState();

    // Getters & setters
    uint32_t getMaxPackets() const { return maxPackets; }
    void setMaxPackets(uint32_t val) { maxPackets = val; }
    bool isRunning() const { return running; }
    void setRunning(bool val) { running = val; }
    uint64_t getUid() const { return uid; }

    // Business logic
    void incrementUid();
  };

} // namespace ndpi
