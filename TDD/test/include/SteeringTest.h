#pragma once

#include <cstdint>

#include <gtest/gtest.h>
#include <pcapplusplus/IPv4Layer.h>

class SteeringTest : public ::testing::Test
{
protected:
    const pcpp::IPv4Address testAddress1{"8.8.8.8"};
    const pcpp::IPv4Address testAddress2{"10.0.0.1"};

    const uint16_t testPort1{53};
    const uint16_t testPort2{88};
    const uint16_t testPort3{80};
    const uint16_t testPort4{8080};
    const uint16_t testPort5{50};
};
