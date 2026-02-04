// Library includes
#include <gtest/gtest.h>

// Project includes
#include "SteeringRule.h"
#include "TestUtils.h"

using namespace pcpp;
using namespace std;
using namespace TDD;

// Constructors

TEST(SteeringRuleTest, isCreatedWithTargetOnly)
{
    IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 53);
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::UDP4, target);

    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(rule->getProtocol()._value, Protocol::UDP4);
    EXPECT_EQ(rule->getPort(), 0);
    EXPECT_EQ(rule->getTarget(), target);
    EXPECT_EQ(rule->getAddress(), IPv4Address::Zero);
}

TEST(SteeringRuleTest, isCreatedWithPortAndTarget)
{
    IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 53);
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, 53, target);

    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(rule->getProtocol()._value, Protocol::TCP4);
    EXPECT_EQ(rule->getPort(), 53);
    EXPECT_EQ(rule->getTarget(), target);
    EXPECT_EQ(rule->getAddress(), IPv4Address::Zero);
}

TEST(SteeringRuleTest, isCreatedWithPortAddressTarget)
{
    IPv4Address targetAddress("8.8.8.8");
    SteeringTarget target(targetAddress, 53);
    IPv4Address address("10.0.0.1");
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, 88, address, target);

    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(rule->getProtocol()._value, Protocol::TCP4);
    EXPECT_EQ(rule->getPort(), 88);
    EXPECT_EQ(rule->getTarget(), target);
    EXPECT_EQ(rule->getAddress(), address);
}

// Getters and Setters

TEST(SteeringRuleTest, getsAddress)
{
    IPv4Address targetAddress("8.8.8.8");
    SteeringTarget target(targetAddress, 53);
    IPv4Address address("10.0.0.1");
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, 88, address, target);

    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(rule->getAddress(), address);
}

TEST(SteeringRuleTest, getsPort)
{
    IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 53);
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, 88, target);

    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(rule->getPort(), 88);
}

TEST(SteeringRuleTest, getsProtocol)
{
    IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 53);
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, target);

    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(rule->getProtocol()._value, Protocol::TCP4);
}

TEST(SteeringRuleTest, getsTarget)
{
    IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 53);
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, target);

    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(rule->getTarget(), target);
}

// Fake Getters

TEST(SteeringRuleTest, getsIdVariantsforTcp4)
{
    IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 53);

    SteeringRule rule1(Protocol::TCP4, target);
    EXPECT_EQ(rule1.getId(), "TCP4");

    SteeringRule rule2(Protocol::TCP4, 80, target);
    EXPECT_EQ(rule2.getId(), "TCP4-80");

    SteeringRule rule3(Protocol::TCP4, 80, IPv4Address("1.2.3.4"), target);
    EXPECT_EQ(rule3.getId(), "TCP4-80-1.2.3.4");
}

TEST(SteeringRuleTest, getsIdVariantsforUdp4)
{
    IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 53);

    SteeringRule rule1(Protocol::UDP4, target);
    EXPECT_EQ(rule1.getId(), "UDP4");

    SteeringRule rule2(Protocol::UDP4, 80, target);
    EXPECT_EQ(rule2.getId(), "UDP4-80");

    SteeringRule rule3(Protocol::UDP4, 80, IPv4Address("1.2.3.4"), target);
    EXPECT_EQ(rule3.getId(), "UDP4-80-1.2.3.4");
}

TEST(SteeringRuleTest, getsIdVariantsforUnknown)
{
    IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 53);

    SteeringRule rule1(Protocol::UNKNOWN, target);
    EXPECT_EQ(rule1.getId(), "UNKNOWN");

    SteeringRule rule2(Protocol::UNKNOWN, 80, target);
    EXPECT_EQ(rule2.getId(), "UNKNOWN-80");

    SteeringRule rule3(Protocol::UNKNOWN, 80, IPv4Address("1.2.3.4"), target);
    EXPECT_EQ(rule3.getId(), "UNKNOWN-80-1.2.3.4");
}

// Business logic

TEST(SteeringRuleTest, matchesPacket)
{
    IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 8080);
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, 80, target);

    auto packetTcp = createTcpPacket(80);

    ASSERT_NE(rule, nullptr);
    EXPECT_TRUE(rule->matches(packetTcp));
}

TEST(SteeringRuleTest, doesnotMatchesPacketByProtocol)
{
    IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 8080);
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, 80, target);

    auto wrongUdp = createUdpPacket(22);

    ASSERT_NE(rule, nullptr);
    EXPECT_FALSE(rule->matches(wrongUdp));
}

TEST(SteeringRuleTest, doesnotMatchesPacketByTcpPort)
{
    IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 8080);
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, 80, target);

    auto packetTcp = createTcpPacket(90);

    ASSERT_NE(rule, nullptr);
    EXPECT_FALSE(rule->matches(packetTcp));
}

TEST(SteeringRuleTest, doesnotMatchesPacketByUdpPort)
{
    IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 8080);
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::UDP4, 80, target);

    auto wrongUdp = createUdpPacket(22);

    ASSERT_NE(rule, nullptr);
    EXPECT_FALSE(rule->matches(wrongUdp));
}

TEST(SteeringRuleTest, doesnotMatchesPacketByAddress)
{
    IPv4Address targetAddress("10.10.10.10");
    SteeringTarget target(targetAddress, 8080);
    IPv4Address address("192.1.1.1");
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, 80, address, target);

    auto wrong = createTcpPacket(80);

    ASSERT_NE(rule, nullptr);
    EXPECT_FALSE(rule->matches(wrong));
}
