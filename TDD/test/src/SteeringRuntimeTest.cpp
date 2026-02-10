// Library includes
#include <gtest/gtest.h>

// Project includes
#include "SteeringRuntime.h"
#include "TestUtils.h"

using namespace pcpp;
using namespace TDD;

class SteeringRuntimeTest : public ::testing::Test
{
protected:
    SteeringRuntime runtime;
};

// Business logic

TEST_F(SteeringRuntimeTest, addsRuleWithTargetOnly)
{
    IPv4Address address(TEST_ADDRESS_1);
    SteeringTarget target(address, TEST_PORT_1);

    auto result = runtime.addRule(Protocol::UDP4, target);
    auto count = runtime.ruleCount();

    EXPECT_TRUE(result);
    EXPECT_EQ(count, 1u);
}

TEST_F(SteeringRuntimeTest, addsRuleWithPortAndTarget)
{
    IPv4Address address(TEST_ADDRESS_1);
    SteeringTarget target(address, TEST_PORT_1);

    auto result = runtime.addRule(Protocol::TCP4, 10, target);
    auto count = runtime.ruleCount();

    EXPECT_TRUE(result);
    EXPECT_EQ(count, 1u);
}

TEST_F(SteeringRuntimeTest, addsRuleWithPortAddressTarget)
{
    IPv4Address targetAddress(TEST_ADDRESS_1);
    SteeringTarget target(targetAddress, TEST_PORT_1);
    IPv4Address address(TEST_ADDRESS_2);

    auto result = runtime.addRule(Protocol::TCP4, 10, address, target);
    auto count = runtime.ruleCount();

    EXPECT_TRUE(result);
    EXPECT_EQ(count, 1u);
}

TEST_F(SteeringRuntimeTest, addsRuleException)
{
    IPv4Address address(TEST_ADDRESS_1);
    SteeringTarget target(address, TEST_PORT_1);

    runtime.addRule(Protocol::UDP4, target);

    EXPECT_THROW(runtime.addRule(Protocol::UDP4, target), DuplicatedTargetException);
}

TEST_F(SteeringRuntimeTest, removesRuleWithProtocolOnly)
{
    IPv4Address address(TEST_ADDRESS_1);
    SteeringTarget target(address, TEST_PORT_1);

    auto result = runtime.addRule(Protocol::UDP4, target);
    auto count = runtime.ruleCount();
    auto resultRemove = runtime.removeRule(Protocol::UDP4);
    auto finalCount = runtime.ruleCount();

    EXPECT_TRUE(result);
    EXPECT_EQ(count, 1u);
    EXPECT_TRUE(resultRemove);
    EXPECT_EQ(finalCount, 0u);
}

TEST_F(SteeringRuntimeTest, removesRuleWithProtocolAndPort)
{
    IPv4Address address(TEST_ADDRESS_1);
    SteeringTarget target(address, TEST_PORT_1);

    auto result = runtime.addRule(Protocol::UDP4, TEST_PORT_2, target);
    auto count = runtime.ruleCount();
    auto resultRemove = runtime.removeRule(Protocol::UDP4, TEST_PORT_2);
    auto finalCount = runtime.ruleCount();

    EXPECT_TRUE(result);
    EXPECT_EQ(count, 1u);
    EXPECT_TRUE(resultRemove);
    EXPECT_EQ(finalCount, 0u);
}

TEST_F(SteeringRuntimeTest, removesRuleWithProtocolAndPortAndAddress)
{
    IPv4Address targetAddress(TEST_ADDRESS_1);
    SteeringTarget target(targetAddress, TEST_PORT_1);
    IPv4Address address(TEST_ADDRESS_2);

    auto result = runtime.addRule(Protocol::UDP4, TEST_PORT_2, address, target);
    auto count = runtime.ruleCount();
    auto resultRemove = runtime.removeRule(Protocol::UDP4, TEST_PORT_2, address);
    auto finalCount = runtime.ruleCount();

    EXPECT_TRUE(result);
    EXPECT_EQ(count, 1u);
    EXPECT_TRUE(resultRemove);
    EXPECT_EQ(finalCount, 0u);
}

TEST_F(SteeringRuntimeTest, removesRuleException)
{
    IPv4Address targetAddress(TEST_ADDRESS_1);
    SteeringTarget target(targetAddress, TEST_PORT_1);

    EXPECT_THROW(runtime.removeRule(Protocol::UDP6), InvalidProtocolException);
}

TEST_F(SteeringRuntimeTest, resetsRules)
{
    IPv4Address address(TEST_ADDRESS_1);
    SteeringTarget target(address, TEST_PORT_1);

    runtime.addRule(Protocol::UDP4, TEST_PORT_2, target);
    auto ruleCount = runtime.ruleCount();
    runtime.reset();

    EXPECT_EQ(ruleCount, 1u);
    EXPECT_EQ(runtime.ruleCount(), 0u);
}

TEST_F(SteeringRuntimeTest, findsMatchingRule)
{
    IPv4Address address(TEST_ADDRESS_1);
    SteeringTarget target(address, TEST_PORT_4);
    runtime.addRule(Protocol::TCP4, TEST_PORT_3, target);

    auto packet = createTcpPacket(TEST_PORT_3);
    auto rule = runtime.ruleSearch(packet);

    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(rule->getTarget().getPort(), TEST_PORT_4);
}
