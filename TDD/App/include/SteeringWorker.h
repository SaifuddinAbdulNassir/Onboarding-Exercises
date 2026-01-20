#pragma once

// Project includes
#include "SteeringRuntime.h"

class SteeringWorker 
{
    SteeringRuntime& runtime;

  public:
  // Constructor
    SteeringWorker(SteeringRuntime& runtime);

    // Packet Processor
    bool process(pcpp::Packet& packet);

    // Packet diverter
    void steer(pcpp::Packet& packet, SteeringTarget& target);
};
