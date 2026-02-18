#pragma once

// Standard includes
#include <cstddef>

namespace np
{

  class NdpiState
  {
  private:
    // Data
    bool running = true;
    size_t uid = 0;

  public:
    // Constructors & destructors
    NdpiState();
    virtual ~NdpiState();

    // Getters & setters
    bool getRunning() const { return running; }
    void setRunning(bool val) { running = val; }
    size_t getUid() const { return uid; }

    // Business logic
    void incrementUid() { uid++; };
  };

} // namespace np
