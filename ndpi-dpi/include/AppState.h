#pragma once

// Standard includes
#include <cstdint>

namespace ndpi
{

  class AppState
  {
  private:
    // Data
    uint32_t maxPackets = 100;
    bool running = true;
    uint64_t uid = 0;

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
    void incrementUid() { uid++; };
  };

} // namespace ndpi
