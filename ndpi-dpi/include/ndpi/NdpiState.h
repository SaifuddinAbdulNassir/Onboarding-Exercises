#pragma once

// Standard includes
#include <cstdint>

namespace ndpi
{

  class NdpiState
  {
  private:
    // Data
    bool running = true;
    uint64_t uid = 0;

  public:
    // Constructors & destructors
    NdpiState();
    virtual ~NdpiState();

    // Getters & setters
    bool getRunning() const { return running; }
    void setRunning(bool val) { running = val; }
    uint64_t getUid() const { return uid; }

    // Business logic
    void incrementUid() { uid++; };
  };

} // namespace ndpi
