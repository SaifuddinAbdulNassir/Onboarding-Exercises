// Library includes
#include <gtest/gtest.h>

// Project includes
#include "exception/InvalidArgumentException.h"
#include "SteeringTarget.h"
#include "SteeringTest.h"
#include "util/TestUtils.h"

using namespace pcpp;
using namespace TDD;

// Constructors

class SteeringTargetTest : public SteeringTest
{
};

TEST_F(SteeringTargetTest, constructsSuccessfullyWithValidArguments)
{
    EXPECT_NO_THROW(SteeringTarget(IPv4Address(testAddress1), testPort3));
}

TEST_F(SteeringTargetTest, constructsWithZeroIpAddress)
{
    EXPECT_THROW(SteeringTarget(IPv4Address::Zero, testPort3), InvalidArgumentException);
}

TEST_F(SteeringTargetTest, constructsWithZeroPortAddress)
{
    EXPECT_THROW(SteeringTarget(IPv4Address(testAddress1), 0), InvalidArgumentException);
}

// Getters and Setters

TEST_F(SteeringTargetTest, getsAddress)
{
    IPv4Address address(testAddress1);
    SteeringTarget target(address, testPort4);

    auto addr = target.getAddress();

    EXPECT_EQ(addr, testAddress1);
}

TEST_F(SteeringTargetTest, getsPort)
{
    IPv4Address address(testAddress1);
    SteeringTarget target(address, testPort4);

    auto port = target.getPort();

    EXPECT_EQ(port, testPort4);
}

TEST_F(SteeringTargetTest, setsAddress)
{
    IPv4Address address(testAddress1);
    SteeringTarget target(address, testPort4);

    address = IPv4Address(testAddress2);
    target.setAddress(address);
    auto addr = target.getAddress();

    EXPECT_EQ(addr, testAddress2);
}

TEST_F(SteeringTargetTest, setsPort)
{
    IPv4Address address(testAddress1);
    SteeringTarget target(address, testPort4);

    target.setPort(443);
    auto port = target.getPort();

    EXPECT_EQ(port, 443);
}

// Relational operators

TEST_F(SteeringTargetTest, comparesEqualRulesCorrectly)
{
    IPv4Address address("1.1.1.1");
    SteeringTarget target1(address, testPort3);
    SteeringTarget target2(address, testPort3);
    address = IPv4Address("2.2.2.2");
    SteeringTarget target3(address, testPort3);

    EXPECT_TRUE(target1 == target2);
    EXPECT_FALSE(target1 == target3);
}
