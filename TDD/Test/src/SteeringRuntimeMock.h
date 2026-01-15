#pragma once
#include <gmock/gmock.h>

#include "SteeringRuntime.h"

class SteeringRuntimeMock : public SteeringRuntime 
{
  public:
    MOCK_METHOD(
        std::shared_ptr<const SteeringRule>,
        ruleSearch,
        (pcpp::Packet& packet),
        (override)
    );
};
