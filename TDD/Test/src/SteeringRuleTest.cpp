#include <gtest/gtest.h>

#include "SteeringRule.h"
#include "TestUtils.h"

TEST(SteeringRuleTest, ConstructorAndGetters)
{
    pcpp::IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 53);
    SteeringRule* rule = new SteeringRule(Protocol::UDP4, target);

    ASSERT_NE(nullptr,rule);
    EXPECT_EQ(Protocol::UDP4, rule->getProtocol()._value);
    EXPECT_EQ(0, rule->getPort());
    EXPECT_EQ(target, rule->getTarget());
    EXPECT_EQ(pcpp::IPv4Address::Zero, rule->getAddress());

    delete rule;
    rule = new SteeringRule(Protocol::TCP4, 53, target);

    ASSERT_NE(nullptr,rule);
    EXPECT_EQ(Protocol::TCP4, rule->getProtocol()._value);
    EXPECT_EQ(53, rule->getPort());
    EXPECT_EQ(target, rule->getTarget());
    EXPECT_EQ(pcpp::IPv4Address::Zero, rule->getAddress());

    delete rule;
    rule = new SteeringRule(Protocol::TCP4, 88, address, target);

    ASSERT_NE(nullptr,rule);
    EXPECT_EQ(Protocol::TCP4, rule->getProtocol()._value);
    EXPECT_EQ(88, rule->getPort());
    EXPECT_EQ(target, rule->getTarget());
    EXPECT_EQ(address, rule->getAddress());

    delete rule;
    rule = nullptr;
}

TEST(SteeringRuleTest, GetIdVariants)
{
    pcpp::IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 53);

    EXPECT_EQ("TCP4",
        SteeringRule(Protocol::TCP4, target).getId());

    EXPECT_EQ("TCP4-80",
        SteeringRule(Protocol::TCP4, 80, target).getId());

    EXPECT_EQ("TCP4-80-1.2.3.4",
        SteeringRule(
            Protocol::TCP4,
            80,
            pcpp::IPv4Address("1.2.3.4"),
            target
        ).getId());
}

TEST(SteeringRuleTest, MatchesPacket)
{
    pcpp::IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 8080);
    SteeringRule* rule = new SteeringRule(Protocol::TCP4, 80, target);

    ASSERT_NE(nullptr, rule);
    auto wrong = createUdpPacket(22);
    EXPECT_FALSE(rule->matches(wrong));

    wrong = createTcpPacket(22);
    EXPECT_FALSE(rule->matches(wrong));

    auto packet = createTcpPacket(80);
    EXPECT_TRUE(rule->matches(packet));

    address = pcpp::IPv4Address("10.10.10.10");

    delete rule;
    rule = new SteeringRule(Protocol::TCP4, 80,address, target);

    ASSERT_NE(nullptr, rule);
    wrong = createTcpPacket(80);
    EXPECT_FALSE(rule->matches(packet));

    delete rule;
    rule = new SteeringRule(Protocol::UDP4, 80,address, target);

    ASSERT_NE(nullptr, rule);
    wrong = createUdpPacket(22);
    EXPECT_FALSE(rule->matches(wrong));

    delete rule;
    rule = nullptr;
}