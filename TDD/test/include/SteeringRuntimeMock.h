#pragma once

// Library includes
#include <gmock/gmock.h>

// Project includes
#include "SteeringRuntime.h"

using namespace pcpp;
using namespace std;
using namespace TDD;

class SteeringRuntimeMock : public SteeringRuntime
{
public:
    MOCK_METHOD(shared_ptr<const SteeringRule>, ruleSearch, (Packet & packet), (override));
};
