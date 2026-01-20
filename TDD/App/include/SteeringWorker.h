#pragma once

// Project includes
#include "SteeringRuntime.h"

using namespace pcpp;

class SteeringWorker 
{
    SteeringRuntime& runtime;

  public:
  // Constructor
    SteeringWorker(SteeringRuntime& runtime);

    // Packet Processor
    bool process(Packet& packet);

    // Packet diverter
    void steer(Packet& packet, SteeringTarget& target);
};
