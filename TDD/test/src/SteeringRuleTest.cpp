// Library includes
#include <gtest/gtest.h>

// Project includes
#include "SteeringRule.h"
#include "util/TestUtils.h"

using namespace pcpp;
using namespace std;
using namespace TDD;

// Constructors

TEST(SteeringRuleTest, isCreatedWithTargetOnly)
{
    IPv4Address address = TEST_ADDRESS_1;
    SteeringTarget target(address, TEST_PORT_1);
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::UDP4, target);

    auto protocol = rule->getProtocol()._value;
    auto port = rule->getPort();
    auto targetGot = rule->getTarget();
    auto addressGot = rule->getAddress();

    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(protocol, Protocol::UDP4);
    EXPECT_EQ(port, 0);
    EXPECT_EQ(targetGot, target);
    EXPECT_EQ(addressGot, IPv4Address::Zero);
}

TEST(SteeringRuleTest, isCreatedWithPortAndTarget)
{
    IPv4Address address = TEST_ADDRESS_1;
    SteeringTarget target(address, TEST_PORT_1);
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, TEST_PORT_1, target);

    auto protocol = rule->getProtocol()._value;
    auto port = rule->getPort();
    auto targetGot = rule->getTarget();
    auto addressGot = rule->getAddress();

    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(protocol, Protocol::TCP4);
    EXPECT_EQ(port, TEST_PORT_1);
    EXPECT_EQ(targetGot, target);
    EXPECT_EQ(addressGot, IPv4Address::Zero);
}

TEST(SteeringRuleTest, isCreatedWithPortAddressTarget)
{
    IPv4Address targetAddress = TEST_ADDRESS_1;
    SteeringTarget target(targetAddress, TEST_PORT_1);
    IPv4Address address = TEST_ADDRESS_2;
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, TEST_PORT_2, address, target);

    auto protocol = rule->getProtocol()._value;
    auto port = rule->getPort();
    auto targetGot = rule->getTarget();
    auto addressGot = rule->getAddress();

    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(protocol, Protocol::TCP4);
    EXPECT_EQ(port, TEST_PORT_2);
    EXPECT_EQ(targetGot, target);
    EXPECT_EQ(addressGot, address);
}

// Getters and Setters

TEST(SteeringRuleTest, getsAddress)
{
    IPv4Address targetAddress = TEST_ADDRESS_1;
    SteeringTarget target(targetAddress, TEST_PORT_1);
    IPv4Address address = TEST_ADDRESS_2;
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, TEST_PORT_2, address, target);

    auto addressGot = rule->getAddress();

    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(addressGot, address);
}

TEST(SteeringRuleTest, getsPort)
{
    IPv4Address address = TEST_ADDRESS_1;
    SteeringTarget target(address, TEST_PORT_1);
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, TEST_PORT_2, target);

    auto port = rule->getPort();

    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(port, TEST_PORT_2);
}

TEST(SteeringRuleTest, getsProtocol)
{
    IPv4Address address(TEST_ADDRESS_1);
    SteeringTarget target(address, TEST_PORT_1);
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, target);

    auto protocol = rule->getProtocol()._value;

    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(protocol, Protocol::TCP4);
}

TEST(SteeringRuleTest, getsTarget)
{
    IPv4Address address = TEST_ADDRESS_1;
    SteeringTarget target(address, TEST_PORT_1);
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, target);

    auto targetGot = rule->getTarget();

    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(targetGot, target);
}

// Fake Getters

TEST(SteeringRuleTest, getsIdVariantsforTcp4)
{
    IPv4Address address = TEST_ADDRESS_1;
    SteeringTarget target(address, TEST_PORT_1);
    SteeringRule rule1(Protocol::TCP4, target);
    SteeringRule rule2(Protocol::TCP4, TEST_PORT_3, target);
    SteeringRule rule3(Protocol::TCP4, TEST_PORT_3, IPv4Address("1.2.3.4"), target);

    auto id1 = rule1.getId();
    auto id2 = rule2.getId();
    auto id3 = rule3.getId();

    EXPECT_EQ(id1, "TCP4");
    EXPECT_EQ(id2, "TCP4-80");
    EXPECT_EQ(id3, "TCP4-80-1.2.3.4");
}

TEST(SteeringRuleTest, getsIdVariantsforUdp4)
{
    IPv4Address address = TEST_ADDRESS_1;
    SteeringTarget target(address, TEST_PORT_1);
    SteeringRule rule1(Protocol::UDP4, target);
    SteeringRule rule2(Protocol::UDP4, TEST_PORT_3, target);
    SteeringRule rule3(Protocol::UDP4, TEST_PORT_3, IPv4Address("1.2.3.4"), target);

    auto id1 = rule1.getId();
    auto id2 = rule2.getId();
    auto id3 = rule3.getId();

    EXPECT_EQ(id1, "UDP4");
    EXPECT_EQ(id2, "UDP4-80");
    EXPECT_EQ(id3, "UDP4-80-1.2.3.4");
}

TEST(SteeringRuleTest, getsIdVariantsforUnknown)
{
    IPv4Address address = TEST_ADDRESS_1;
    SteeringTarget target(address, TEST_PORT_1);
    SteeringRule rule1(Protocol::UNKNOWN, target);
    SteeringRule rule2(Protocol::UNKNOWN, TEST_PORT_3, target);
    SteeringRule rule3(Protocol::UNKNOWN, TEST_PORT_3, IPv4Address("1.2.3.4"), target);

    auto id1 = rule1.getId();
    auto id2 = rule2.getId();
    auto id3 = rule3.getId();

    EXPECT_EQ(id1, "UNKNOWN");
    EXPECT_EQ(id2, "UNKNOWN-80");
    EXPECT_EQ(id3, "UNKNOWN-80-1.2.3.4");
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
