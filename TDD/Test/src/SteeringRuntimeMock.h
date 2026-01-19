#pragma once

// Library includes
#include <gmock/gmock.h>

// Project includes
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
