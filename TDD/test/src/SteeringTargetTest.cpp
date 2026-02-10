// Library includes
#include <gtest/gtest.h>

// Project includes
#include "exception/InvalidArgumentException.h"
#include "SteeringTarget.h"
#include "util/TestUtils.h"

using namespace pcpp;
using namespace TDD;

// Constructors

TEST(SteeringTargetTest, constructsSuccessfullyWithValidArguments)
{
    EXPECT_NO_THROW(SteeringTarget(IPv4Address(TEST_ADDRESS_1), TEST_PORT_3));
}

TEST(SteeringTargetTest, constructsWithZeroIpAddress)
{
    EXPECT_THROW(SteeringTarget(IPv4Address::Zero, TEST_PORT_3), InvalidArgumentException);
}

TEST(SteeringTargetTest, constructsWithZeroPortAddress)
{
    EXPECT_THROW(SteeringTarget(IPv4Address(TEST_ADDRESS_1), 0), InvalidArgumentException);
}

// Getters and Setters

TEST(SteeringTargetTest, getsAddress)
{
    IPv4Address address(TEST_ADDRESS_1);
    SteeringTarget target(address, TEST_PORT_4);

    auto addr = target.getAddress();

    EXPECT_EQ(addr, TEST_ADDRESS_1);
}

TEST(SteeringTargetTest, getsPort)
{
    IPv4Address address(TEST_ADDRESS_1);
    SteeringTarget target(address, TEST_PORT_4);

    auto port = target.getPort();

    EXPECT_EQ(port, TEST_PORT_4);
}

TEST(SteeringTargetTest, setsAddress)
{
    IPv4Address address(TEST_ADDRESS_1);
    SteeringTarget target(address, TEST_PORT_4);

    address = IPv4Address(TEST_ADDRESS_2);
    target.setAddress(address);
    auto addr = target.getAddress();

    EXPECT_EQ(addr, TEST_ADDRESS_2);
}

TEST(SteeringTargetTest, setsPort)
{
    IPv4Address address(TEST_ADDRESS_1);
    SteeringTarget target(address, TEST_PORT_4);

    target.setPort(443);
    auto port = target.getPort();

    EXPECT_EQ(port, 443);
}

// Relational operators

TEST(SteeringTargetTest, comparesEqualRulesCorrectly)
{
    IPv4Address address("1.1.1.1");
    SteeringTarget target1(address, TEST_PORT_3);
    SteeringTarget target2(address, TEST_PORT_3);
    address = IPv4Address("2.2.2.2");
    SteeringTarget target3(address, TEST_PORT_3);

    EXPECT_TRUE(target1 == target2);
    EXPECT_FALSE(target1 == target3);
}
