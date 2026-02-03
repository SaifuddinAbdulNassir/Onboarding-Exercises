#pragma once

// Project includes
#include "SteeringRuntime.h"

namespace TDD
{

  class SteeringWorker 
  {
    private:
      SteeringRuntime &runtime;

    public:
    // Constructor
      SteeringWorker(SteeringRuntime &runtime);

      // Business logic
      bool process(pcpp::Packet &packet);
      void steer(pcpp::Packet &packet, SteeringTarget &target);
  };
  
} // namespace TDD
