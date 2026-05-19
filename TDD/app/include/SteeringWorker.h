#pragma once

// Project includes
#include "SteeringRuntime.h"

namespace TDD
{

  class SteeringWorker
  {
  private:
    // Data
    SteeringRuntime &runtime;

  public:
    // Constructors & destructors
    SteeringWorker(SteeringRuntime &runtime);
    virtual ~SteeringWorker();

    // Business logic
    bool process(pcpp::Packet &packet);
    void steer(pcpp::Packet &packet, SteeringTarget &target);
  };

} // namespace TDD
