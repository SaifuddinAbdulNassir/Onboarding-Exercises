// Library includes
#include <gtest/gtest.h>

// Project includes
#include "exception/InvalidArgumentException.h"
#include "SteeringTarget.h"

TEST(SteeringTargetTest, constructsSuccessfullyWithValidArguments)
{
    EXPECT_NO_THROW(
        SteeringTarget(pcpp::IPv4Address("8.8.8.8"), 80));
}

TEST(SteeringTargetTest, constructsWithZeroIpAddress)
{
    EXPECT_THROW(
        SteeringTarget(pcpp::IPv4Address::Zero, 80),
        InvalidArgumentException
    );
}

TEST(SteeringTargetTest, constructsWithZeroPortAddress)
{
    EXPECT_THROW(
        SteeringTarget(pcpp::IPv4Address("8.8.8.8"), 0),
        InvalidArgumentException
    );
}

TEST(SteeringTargetTest, getsAddress)
{
    pcpp::IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 8080);
 
    EXPECT_EQ("8.8.8.8", target.getAddress().toString());
}

TEST(SteeringTargetTest, getsPort)
{
    pcpp::IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 8080);
 
    EXPECT_EQ(8080, target.getPort());
}

TEST(SteeringTargetTest, setsAddress)
{
    pcpp::IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 8080);
 
    address = pcpp::IPv4Address("10.0.0.1");
    target.setAddress(address);
    
    EXPECT_EQ("10.0.0.1", target.getAddress().toString());
}

TEST(SteeringTargetTest, setsPort)
{
    pcpp::IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 8080);
 
    target.setPort(443);

    EXPECT_EQ(443, target.getPort());
}

TEST(SteeringTargetTest, comparesEqualRulesCorrectly)
{
    pcpp::IPv4Address address("1.1.1.1");
    SteeringTarget a(address, 80);
    SteeringTarget b(address, 80);
    address = pcpp::IPv4Address("2.2.2.2");
    SteeringTarget c(address, 80);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}
