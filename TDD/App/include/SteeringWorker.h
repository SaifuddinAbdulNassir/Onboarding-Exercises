#pragma once

// Project includes
#include "SteeringRuntime.h"

class SteeringWorker 
{
    SteeringRuntime& runtime;

  public:
  // Constructor
    SteeringWorker(SteeringRuntime& runtime);

    // Business logic
    bool process(pcpp::Packet& packet);
    void steer(pcpp::Packet& packet, SteeringTarget& target);
};
