// Library includes
#include <gtest/gtest.h>

// Project includes
#include "SteeringRule.h"
#include "SteeringTest.h"
#include "util/TestUtils.h"

using namespace pcpp;
using namespace std;
using namespace TDD;

// Constructors

class SteeringRuleTest : public SteeringTest
{
};

TEST_F(SteeringRuleTest, isCreatedWithTargetOnly)
{
    IPv4Address address = testAddress1;
    SteeringTarget target(address, testPort1);
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

TEST_F(SteeringRuleTest, isCreatedWithPortAndTarget)
{
    IPv4Address address = testAddress1;
    SteeringTarget target(address, testPort1);
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, testPort1, target);

    auto protocol = rule->getProtocol()._value;
    auto port = rule->getPort();
    auto targetGot = rule->getTarget();
    auto addressGot = rule->getAddress();

    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(protocol, Protocol::TCP4);
    EXPECT_EQ(port, testPort1);
    EXPECT_EQ(targetGot, target);
    EXPECT_EQ(addressGot, IPv4Address::Zero);
}

TEST_F(SteeringRuleTest, isCreatedWithPortAddressTarget)
{
    IPv4Address targetAddress = testAddress1;
    SteeringTarget target(targetAddress, testPort1);
    IPv4Address address = testAddress2;
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, testPort2, address, target);

    auto protocol = rule->getProtocol()._value;
    auto port = rule->getPort();
    auto targetGot = rule->getTarget();
    auto addressGot = rule->getAddress();

    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(protocol, Protocol::TCP4);
    EXPECT_EQ(port, testPort2);
    EXPECT_EQ(targetGot, target);
    EXPECT_EQ(addressGot, address);
}

// Getters and Setters

TEST_F(SteeringRuleTest, getsAddress)
{
    IPv4Address targetAddress = testAddress1;
    SteeringTarget target(targetAddress, testPort1);
    IPv4Address address = testAddress2;
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, testPort2, address, target);

    auto addressGot = rule->getAddress();

    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(addressGot, address);
}

TEST_F(SteeringRuleTest, getsPort)
{
    IPv4Address address = testAddress1;
    SteeringTarget target(address, testPort1);
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, testPort2, target);

    auto port = rule->getPort();

    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(port, testPort2);
}

TEST_F(SteeringRuleTest, getsProtocol)
{
    IPv4Address address(testAddress1);
    SteeringTarget target(address, testPort1);
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, target);

    auto protocol = rule->getProtocol()._value;

    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(protocol, Protocol::TCP4);
}

TEST_F(SteeringRuleTest, getsTarget)
{
    IPv4Address address = testAddress1;
    SteeringTarget target(address, testPort1);
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, target);

    auto targetGot = rule->getTarget();

    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(targetGot, target);
}

// Fake Getters

TEST_F(SteeringRuleTest, getsIdVariantsforTcp4)
{
    IPv4Address address = testAddress1;
    SteeringTarget target(address, testPort1);
    SteeringRule rule1(Protocol::TCP4, target);
    SteeringRule rule2(Protocol::TCP4, testPort3, target);
    SteeringRule rule3(Protocol::TCP4, testPort3, IPv4Address("1.2.3.4"), target);

    auto id1 = rule1.getId();
    auto id2 = rule2.getId();
    auto id3 = rule3.getId();

    EXPECT_EQ(id1, "TCP4");
    EXPECT_EQ(id2, "TCP4-80");
    EXPECT_EQ(id3, "TCP4-80-1.2.3.4");
}

TEST_F(SteeringRuleTest, getsIdVariantsforUdp4)
{
    IPv4Address address = testAddress1;
    SteeringTarget target(address, testPort1);
    SteeringRule rule1(Protocol::UDP4, target);
    SteeringRule rule2(Protocol::UDP4, testPort3, target);
    SteeringRule rule3(Protocol::UDP4, testPort3, IPv4Address("1.2.3.4"), target);

    auto id1 = rule1.getId();
    auto id2 = rule2.getId();
    auto id3 = rule3.getId();

    EXPECT_EQ(id1, "UDP4");
    EXPECT_EQ(id2, "UDP4-80");
    EXPECT_EQ(id3, "UDP4-80-1.2.3.4");
}

TEST_F(SteeringRuleTest, getsIdVariantsforUnknown)
{
    IPv4Address address = testAddress1;
    SteeringTarget target(address, testPort1);
    SteeringRule rule1(Protocol::UNKNOWN, target);
    SteeringRule rule2(Protocol::UNKNOWN, testPort3, target);
    SteeringRule rule3(Protocol::UNKNOWN, testPort3, IPv4Address("1.2.3.4"), target);

    auto id1 = rule1.getId();
    auto id2 = rule2.getId();
    auto id3 = rule3.getId();

    EXPECT_EQ(id1, "UNKNOWN");
    EXPECT_EQ(id2, "UNKNOWN-80");
    EXPECT_EQ(id3, "UNKNOWN-80-1.2.3.4");
}

// Business logic

TEST_F(SteeringRuleTest, matchesPacket)
{
    IPv4Address address = testAddress1;
    SteeringTarget target(address, testPort4);
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, testPort3, target);

    auto packetTcp = createTcpPacket(testPort3);

    ASSERT_NE(rule, nullptr);
    EXPECT_TRUE(rule->matches(packetTcp));
}

TEST_F(SteeringRuleTest, doesnotMatchesPacketByProtocol)
{
    IPv4Address address(testAddress1);
    SteeringTarget target(address, testPort4);
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, testPort3, target);

    auto wrongUdp = createUdpPacket(22);

    ASSERT_NE(rule, nullptr);
    EXPECT_FALSE(rule->matches(wrongUdp));
}

TEST_F(SteeringRuleTest, doesnotMatchesPacketByTcpPort)
{
    IPv4Address address(testAddress1);
    SteeringTarget target(address, testPort4);
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, testPort3, target);

    auto packetTcp = createTcpPacket(90);

    ASSERT_NE(rule, nullptr);
    EXPECT_FALSE(rule->matches(packetTcp));
}

TEST_F(SteeringRuleTest, doesnotMatchesPacketByUdpPort)
{
    IPv4Address address(testAddress1);
    SteeringTarget target(address, testPort4);
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::UDP4, testPort3, target);

    auto wrongUdp = createUdpPacket(22);

    ASSERT_NE(rule, nullptr);
    EXPECT_FALSE(rule->matches(wrongUdp));
}

TEST_F(SteeringRuleTest, doesnotMatchesPacketByAddress)
{
    IPv4Address targetAddress("10.10.10.10");
    SteeringTarget target(targetAddress, testPort4);
    IPv4Address address("192.1.1.1");
    unique_ptr<SteeringRule> rule = make_unique<SteeringRule>(Protocol::TCP4, testPort3, address, target);

    auto wrong = createTcpPacket(testPort3);

    ASSERT_NE(rule, nullptr);
    EXPECT_FALSE(rule->matches(wrong));
}
