#pragma once

// Standard includes
#include <cstdint>

class AppState 
{
  public:
    // Constructors & destructors
    AppState();
    ~AppState();
  
    // Getters & setters
    uint32_t getMaxPackets() const { return maxPackets; }
    void setMaxPackets(uint32_t val) { maxPackets = val; }
    bool isRunning() const { return running; }
    void setRunning(bool val) { running = val; }
    uint64_t getUid() const { return uid; }
    void incrementUid() { uid++; }

  private:
    // Data
    uint32_t maxPackets;
    bool running;
    uint64_t uid;
};
