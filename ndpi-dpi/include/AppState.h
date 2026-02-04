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
    bool getRunning() const { return running; }
    uint64_t getUid() const { return uid; }
    void setMaxPackets(uint32_t val) { maxPackets = val; }
    void setRunning(bool val) { running = val; }

    // Business logic
    void incrementUid();
  };

} // namespace ndpi
