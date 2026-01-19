#pragma once

// Standard includes
#include <cstdint>

class AppState 
{
  public:
    static uint32_t maxPackets;
    static bool running;
    static uint64_t uid;
};
