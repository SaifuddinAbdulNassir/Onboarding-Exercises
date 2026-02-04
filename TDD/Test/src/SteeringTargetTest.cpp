// Library includes
#include <gtest/gtest.h>

// Project includes
#include "exception/InvalidArgumentException.h"
#include "SteeringTarget.h"

using namespace pcpp;
using namespace TDD;

// Constructors

TEST(SteeringTargetTest, constructsSuccessfullyWithValidArguments)
{
    EXPECT_NO_THROW(SteeringTarget(IPv4Address("8.8.8.8"), 80));
}

TEST(SteeringTargetTest, constructsWithZeroIpAddress)
{
    EXPECT_THROW(SteeringTarget(IPv4Address::Zero, 80), InvalidArgumentException);
}

TEST(SteeringTargetTest, constructsWithZeroPortAddress)
{
    EXPECT_THROW(SteeringTarget(IPv4Address("8.8.8.8"), 0), InvalidArgumentException);
}

// Getters and Setters

TEST(SteeringTargetTest, getsAddress)
{
    IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 8080);

    auto addr = target.getAddress();

    EXPECT_EQ(addr.toString(), "8.8.8.8");
}

TEST(SteeringTargetTest, getsPort)
{
    IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 8080);

    auto port = target.getPort();

    EXPECT_EQ(port, 8080);
}

TEST(SteeringTargetTest, setsAddress)
{
    IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 8080);

    address = IPv4Address("10.0.0.1");
    target.setAddress(address);
    auto addr = target.getAddress();

    EXPECT_EQ(addr.toString(), "10.0.0.1");
}

TEST(SteeringTargetTest, setsPort)
{
    IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 8080);

    target.setPort(443);
    auto port = target.getPort();

    EXPECT_EQ(port, 443);
}

// Relational operators

TEST(SteeringTargetTest, comparesEqualRulesCorrectly)
{
    IPv4Address address("1.1.1.1");
    SteeringTarget target1(address, 80);
    SteeringTarget target2(address, 80);
    address = IPv4Address("2.2.2.2");
    SteeringTarget target3(address, 80);

    EXPECT_TRUE(target1 == target2);
    EXPECT_FALSE(target1 == target3);
}
