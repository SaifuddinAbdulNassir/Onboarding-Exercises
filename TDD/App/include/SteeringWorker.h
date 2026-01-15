#pragma once

#include "SteeringRuntime.h"

class SteeringWorker 
{
    SteeringRuntime& runtime;

  public:
    SteeringWorker(SteeringRuntime& runtime);

    bool process(pcpp::Packet& packet);
    void steer(pcpp::Packet& packet, SteeringTarget& target);
};
