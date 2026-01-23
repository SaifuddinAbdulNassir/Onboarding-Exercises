// Library includes
#include <gtest/gtest.h>

// Project includes
#include "SteeringRuntime.h"
#include "TestUtils.h"

class SteeringRuntimeTest : public ::testing::Test
{
  protected:
    SteeringRuntime runtime;
};

// Business logic tests

TEST_F(SteeringRuntimeTest, addsRuleWithTargetOnly)
{
    pcpp::IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 53);

    EXPECT_TRUE(runtime.addRule(Protocol::UDP4, target));
    EXPECT_EQ(runtime.ruleCount(), 1u);
}

TEST_F(SteeringRuntimeTest, addsRuleWithPortAndTarget)
{
    pcpp::IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 53);

    EXPECT_TRUE(runtime.addRule(Protocol::TCP4, 10, target));
    EXPECT_EQ(runtime.ruleCount(), 1u);
}

TEST_F(SteeringRuntimeTest, addsRuleWithPortAddressTarget)
{
    pcpp::IPv4Address targetAddress("8.8.8.8");
    SteeringTarget target(targetAddress, 53);
    pcpp::IPv4Address address("10.0.0.1");

    EXPECT_TRUE(runtime.addRule(Protocol::TCP4, 10, address, target));
    EXPECT_EQ(runtime.ruleCount(), 1u);
}

TEST_F(SteeringRuntimeTest, addsRuleException)
{
    pcpp::IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 53);

    runtime.addRule(Protocol::UDP4, target);

    EXPECT_THROW(runtime.addRule(Protocol::UDP4, target), DuplicatedTargetException);
}

TEST_F(SteeringRuntimeTest, removesRuleWithProtocolOnly)
{
    pcpp::IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 53);

    EXPECT_TRUE(runtime.addRule(Protocol::UDP4, target));
    EXPECT_EQ(runtime.ruleCount(), 1u);
    EXPECT_TRUE(runtime.removeRule(Protocol::UDP4));
    EXPECT_EQ(runtime.ruleCount(), 0u);
}

TEST_F(SteeringRuntimeTest, removesRuleWithProtocolAndPort)
{
    pcpp::IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 53);

    EXPECT_TRUE(runtime.addRule(Protocol::UDP4, 50, target));
    EXPECT_EQ(runtime.ruleCount(), 1u);
    EXPECT_TRUE(runtime.removeRule(Protocol::UDP4, 50));
    EXPECT_EQ(runtime.ruleCount(), 0u);
}

TEST_F(SteeringRuntimeTest, removesRuleWithProtocolAndPortAndAddress)
{
    pcpp::IPv4Address targetAddress("8.8.8.8");
    SteeringTarget target(targetAddress, 53);
    pcpp::IPv4Address address("10.0.0.1");

    EXPECT_TRUE(runtime.addRule(Protocol::UDP4, 50, address, target));
    EXPECT_EQ(runtime.ruleCount(), 1u);
    EXPECT_TRUE(runtime.removeRule(Protocol::UDP4, 50, address));
    EXPECT_EQ(runtime.ruleCount(), 0u);
}

TEST_F(SteeringRuntimeTest, removesRuleException)
{
    pcpp::IPv4Address targetAddress("8.8.8.8");
    SteeringTarget target(targetAddress, 53);

    EXPECT_TRUE(runtime.addRule(Protocol::UDP4, target));
    EXPECT_EQ(runtime.ruleCount(), 1u);
    EXPECT_THROW(runtime.removeRule(Protocol::UDP6), InvalidProtocolException);
}

TEST_F(SteeringRuntimeTest, resetsRules)
{
    pcpp::IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 53);

    runtime.addRule(Protocol::UDP4, 50, target);
    auto ruleCount = runtime.ruleCount();
    runtime.reset();

    EXPECT_EQ(ruleCount, 1u);
    EXPECT_EQ(runtime.ruleCount(), 0u);
}

TEST_F(SteeringRuntimeTest, findsMatchingRule)
{
    pcpp::IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 8080);
    runtime.addRule(Protocol::TCP4, 80, target);

    auto packet = createTcpPacket(80);
    auto rule = runtime.ruleSearch(packet);

    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(rule->getTarget().getPort(), 8080);
}
