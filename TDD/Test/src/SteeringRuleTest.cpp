// Library includes
#include <gtest/gtest.h>

// Project includes
#include "SteeringRule.h"
#include "TestUtils.h"

TEST(SteeringRuleTest, isCreatedWithTargetOnly)
{
    pcpp::IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 53);
    std::unique_ptr<SteeringRule> rule = std::make_unique<SteeringRule>(Protocol::UDP4, target);

    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(rule->getProtocol()._value, Protocol::UDP4);
    EXPECT_EQ(rule->getPort(), 0);
    EXPECT_EQ(rule->getTarget(), target);
    EXPECT_EQ(rule->getAddress(), pcpp::IPv4Address::Zero);
}

TEST(SteeringRuleTest, isCreatedWithPortAndTarget)
{
    pcpp::IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 53);
    std::unique_ptr<SteeringRule> rule = std::make_unique<SteeringRule>(Protocol::TCP4, 53, target);

    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(rule->getProtocol()._value, Protocol::TCP4);
    EXPECT_EQ(rule->getPort(), 53);
    EXPECT_EQ(rule->getTarget(), target);
    EXPECT_EQ(rule->getAddress(), pcpp::IPv4Address::Zero);
}

TEST(SteeringRuleTest, isCreatedWithPortAddressTarget)
{
    pcpp::IPv4Address targetAddress("8.8.8.8");
    SteeringTarget target(targetAddress, 53);
    pcpp::IPv4Address address("10.0.0.1");
    std::unique_ptr<SteeringRule> rule = std::make_unique<SteeringRule>(Protocol::TCP4, 88, address, target);
    
    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(rule->getProtocol()._value, Protocol::TCP4);
    EXPECT_EQ(rule->getPort(), 88);
    EXPECT_EQ(rule->getTarget(), target);
    EXPECT_EQ(rule->getAddress(), address);
}

TEST(SteeringRuleTest, getsAddress)
{
    pcpp::IPv4Address targetAddress("8.8.8.8");
    SteeringTarget target(targetAddress, 53);
    pcpp::IPv4Address address("10.0.0.1");
    std::unique_ptr<SteeringRule> rule = std::make_unique<SteeringRule>(Protocol::TCP4, 88, address, target);
    
    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(rule->getAddress(), address);
}

TEST(SteeringRuleTest, getsIdVariants)
{
    pcpp::IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 53);

    EXPECT_EQ(SteeringRule(Protocol::TCP4, target).getId(), "TCP4");
    EXPECT_EQ(SteeringRule(Protocol::TCP4, 80, target).getId(), "TCP4-80");
    EXPECT_EQ(
        SteeringRule(
            Protocol::TCP4,
            80,
            pcpp::IPv4Address("1.2.3.4"),
            target
        ).getId(),
        "TCP4-80-1.2.3.4"
    );
}

TEST(SteeringRuleTest, getsPort)
{
    pcpp::IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 53);
    std::unique_ptr<SteeringRule> rule = std::make_unique<SteeringRule>(Protocol::TCP4, 88, target);
    
    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(rule->getPort(), 88);
}

TEST(SteeringRuleTest, getsProtocol)
{
    pcpp::IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 53);
    std::unique_ptr<SteeringRule> rule = std::make_unique<SteeringRule>(Protocol::TCP4, target);
    
    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(rule->getProtocol()._value, Protocol::TCP4);
}

TEST(SteeringRuleTest, getsTarget)
{
    pcpp::IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 53);
    std::unique_ptr<SteeringRule> rule = std::make_unique<SteeringRule>(Protocol::TCP4, target);
    
    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(rule->getTarget(), target);
}

TEST(SteeringRuleTest, matchesPacket)
{
    pcpp::IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 8080);
    std::unique_ptr<SteeringRule> rule = std::make_unique<SteeringRule>(Protocol::TCP4, 80, target);
    
    auto packetTcp = createTcpPacket(80);

    ASSERT_NE(rule, nullptr);
    EXPECT_TRUE(rule->matches(packetTcp));
}

TEST(SteeringRuleTest, doesnotMatchesPacketByProtocol)
{
    pcpp::IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 8080);
    std::unique_ptr<SteeringRule> rule = std::make_unique<SteeringRule>(Protocol::TCP4, 80, target);
    
    auto wrongUdp = createUdpPacket(22);

    ASSERT_NE(rule, nullptr);
    EXPECT_FALSE(rule->matches(wrongUdp));
}

TEST(SteeringRuleTest, doesnotMatchesPacketByTcpPort)
{
    pcpp::IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 8080);
    std::unique_ptr<SteeringRule> rule = std::make_unique<SteeringRule>(Protocol::TCP4, 80, target);
    
    auto packetTcp = createTcpPacket(90);

    ASSERT_NE(rule, nullptr);
    EXPECT_FALSE(rule->matches(packetTcp));
}

TEST(SteeringRuleTest, doesnotMatchesPacketByUdpPort)
{
    pcpp::IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 8080);
    std::unique_ptr<SteeringRule> rule = std::make_unique<SteeringRule>(Protocol::UDP4, 80, target);
    
    auto wrongUdp = createUdpPacket(22);

    ASSERT_NE(rule, nullptr);
    EXPECT_FALSE(rule->matches(wrongUdp));
}

TEST(SteeringRuleTest, doesnotMatchesPacketByAddress)
{
    pcpp::IPv4Address targetAddress("10.10.10.10");
    SteeringTarget target(targetAddress, 8080);
    pcpp::IPv4Address address("192.1.1.1");
    std::unique_ptr<SteeringRule> rule = std::make_unique<SteeringRule>(Protocol::TCP4, 80, address, target);
    
    auto wrong = createTcpPacket(80);

    ASSERT_NE(rule, nullptr);
    EXPECT_FALSE(rule->matches(wrong));
}
