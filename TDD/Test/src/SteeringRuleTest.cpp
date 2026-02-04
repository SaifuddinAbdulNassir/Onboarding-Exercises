// Library includes
#include <gtest/gtest.h>

// Project includes
#include "SteeringRule.h"
#include "TestUtils.h"

using namespace pcpp;
using namespace std;
using namespace TDD;

// Constants
const IPv4Address TEST_ADDRESS_1("8.8.8.8");
const IPv4Address TEST_ADDRESS_2("10.0.0.1");
const uint16_t TEST_PORT_1 = 53;
const uint16_t TEST_PORT_2 = 88;
const uint16_t TEST_PORT_3 = 80;
const uint16_t TEST_PORT_4 = 8080;

// Constructors

TEST(SteeringRuleTest, isCreatedWithTargetOnly)
{
    IPv4Address address = TEST_ADDRESS_1;
    SteeringTarget target(address, TEST_PORT_1);
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::UDP4, target);

    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(rule->getProtocol()._value, Protocol::UDP4);
    EXPECT_EQ(rule->getPort(), 0);
    EXPECT_EQ(rule->getTarget(), target);
    EXPECT_EQ(rule->getAddress(), IPv4Address::Zero);
}

TEST(SteeringRuleTest, isCreatedWithPortAndTarget)
{
    IPv4Address address = TEST_ADDRESS_1;
    SteeringTarget target(address, TEST_PORT_1);
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, TEST_PORT_1, target);

    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(rule->getProtocol()._value, Protocol::TCP4);
    EXPECT_EQ(rule->getPort(), TEST_PORT_1);
    EXPECT_EQ(rule->getTarget(), target);
    EXPECT_EQ(rule->getAddress(), IPv4Address::Zero);
}

TEST(SteeringRuleTest, isCreatedWithPortAddressTarget)
{
    IPv4Address targetAddress = TEST_ADDRESS_1;
    SteeringTarget target(targetAddress, TEST_PORT_1);
    IPv4Address address = TEST_ADDRESS_2;
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, TEST_PORT_2, address, target);

    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(rule->getProtocol()._value, Protocol::TCP4);
    EXPECT_EQ(rule->getPort(), TEST_PORT_2);
    EXPECT_EQ(rule->getTarget(), target);
    EXPECT_EQ(rule->getAddress(), address);
}

// Getters and Setters

TEST(SteeringRuleTest, getsAddress)
{
    IPv4Address targetAddress = TEST_ADDRESS_1;
    SteeringTarget target(targetAddress, TEST_PORT_1);
    IPv4Address address = TEST_ADDRESS_2;
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, TEST_PORT_2, address, target);

    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(rule->getAddress(), address);
}

TEST(SteeringRuleTest, getsPort)
{
    IPv4Address address = TEST_ADDRESS_1;
    SteeringTarget target(address, TEST_PORT_1);
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, TEST_PORT_2, target);

    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(rule->getPort(), TEST_PORT_2);
}

TEST(SteeringRuleTest, getsProtocol)
{
    IPv4Address address(TEST_ADDRESS_1);
    SteeringTarget target(address, TEST_PORT_1);
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, target);

    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(rule->getProtocol()._value, Protocol::TCP4);
}

TEST(SteeringRuleTest, getsTarget)
{
    IPv4Address address = TEST_ADDRESS_1;
    SteeringTarget target(address, TEST_PORT_1);
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, target);

    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(rule->getTarget(), target);
}

// Fake Getters

TEST(SteeringRuleTest, getsIdVariantsforTcp4)
{
    IPv4Address address = TEST_ADDRESS_1;
    SteeringTarget target(address, TEST_PORT_1);
    SteeringRule rule1(Protocol::TCP4, target);
    SteeringRule rule2(Protocol::TCP4, TEST_PORT_3, target);
    SteeringRule rule3(Protocol::TCP4, TEST_PORT_3, IPv4Address("1.2.3.4"), target);

    EXPECT_EQ(rule1.getId(), "TCP4");
    EXPECT_EQ(rule2.getId(), "TCP4-80");
    EXPECT_EQ(rule3.getId(), "TCP4-80-1.2.3.4");
}

TEST(SteeringRuleTest, getsIdVariantsforUdp4)
{
    IPv4Address address = TEST_ADDRESS_1;
    SteeringTarget target(address, TEST_PORT_1);
    SteeringRule rule1(Protocol::UDP4, target);
    SteeringRule rule2(Protocol::UDP4, TEST_PORT_3, target);
    SteeringRule rule3(Protocol::UDP4, TEST_PORT_3, IPv4Address("1.2.3.4"), target);

    EXPECT_EQ(rule1.getId(), "UDP4");
    EXPECT_EQ(rule2.getId(), "UDP4-80");
    EXPECT_EQ(rule3.getId(), "UDP4-80-1.2.3.4");
}

TEST(SteeringRuleTest, getsIdVariantsforUnknown)
{
    IPv4Address address = TEST_ADDRESS_1;
    SteeringTarget target(address, TEST_PORT_1);
    SteeringRule rule1(Protocol::UNKNOWN, target);
    SteeringRule rule2(Protocol::UNKNOWN, TEST_PORT_3, target);
    SteeringRule rule3(Protocol::UNKNOWN, TEST_PORT_3, IPv4Address("1.2.3.4"), target);

    EXPECT_EQ(rule1.getId(), "UNKNOWN");
    EXPECT_EQ(rule2.getId(), "UNKNOWN-80");
    EXPECT_EQ(rule3.getId(), "UNKNOWN-80-1.2.3.4");
}

// Business logic

TEST(SteeringRuleTest, matchesPacket)
{
    IPv4Address address = TEST_ADDRESS_1;
    SteeringTarget target(address, TEST_PORT_4);
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, TEST_PORT_3, target);

    auto packetTcp = createTcpPacket(TEST_PORT_3);

    ASSERT_NE(rule, nullptr);
    EXPECT_TRUE(rule->matches(packetTcp));
}

TEST(SteeringRuleTest, doesnotMatchesPacketByProtocol)
{
    IPv4Address address(TEST_ADDRESS_1);
    SteeringTarget target(address, TEST_PORT_4);
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, TEST_PORT_3, target);

    auto wrongUdp = createUdpPacket(22);

    ASSERT_NE(rule, nullptr);
    EXPECT_FALSE(rule->matches(wrongUdp));
}

TEST(SteeringRuleTest, doesnotMatchesPacketByTcpPort)
{
    IPv4Address address(TEST_ADDRESS_1);
    SteeringTarget target(address, TEST_PORT_4);
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, TEST_PORT_3, target);

    auto packetTcp = createTcpPacket(90);

    ASSERT_NE(rule, nullptr);
    EXPECT_FALSE(rule->matches(packetTcp));
}

TEST(SteeringRuleTest, doesnotMatchesPacketByUdpPort)
{
    IPv4Address address(TEST_ADDRESS_1);
    SteeringTarget target(address, TEST_PORT_4);
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::UDP4, TEST_PORT_3, target);

    auto wrongUdp = createUdpPacket(22);

    ASSERT_NE(rule, nullptr);
    EXPECT_FALSE(rule->matches(wrongUdp));
}

TEST(SteeringRuleTest, doesnotMatchesPacketByAddress)
{
    IPv4Address targetAddress("10.10.10.10");
    SteeringTarget target(targetAddress, TEST_PORT_4);
    IPv4Address address("192.1.1.1");
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, TEST_PORT_3, address, target);

    auto wrong = createTcpPacket(TEST_PORT_3);

    ASSERT_NE(rule, nullptr);
    EXPECT_FALSE(rule->matches(wrong));
}
