// Library includes
#include <gtest/gtest.h>

// Project includes
#include "exception/DuplicatedTargetException.h"
#include "exception/InvalidProtocolException.h"
#include "SteeringRuntime.h"
#include "SteeringTest.h"
#include "util/TestUtils.h"

using namespace pcpp;
using namespace TDD;

class SteeringRuntimeTest : public SteeringTest
{
protected:
    SteeringRuntime runtime;
};

// Business logic

TEST_F(SteeringRuntimeTest, addsRuleWithTargetOnly)
{
    IPv4Address address(testAddress1);
    SteeringTarget target(address, testPort1);

    auto result = runtime.addRule(Protocol::UDP4, target);
    auto count = runtime.ruleCount();

    EXPECT_TRUE(result);
    EXPECT_EQ(count, 1u);
}

TEST_F(SteeringRuntimeTest, addsRuleWithPortAndTarget)
{
    IPv4Address address(testAddress1);
    SteeringTarget target(address, testPort1);

    auto result = runtime.addRule(Protocol::TCP4, 10, target);
    auto count = runtime.ruleCount();

    EXPECT_TRUE(result);
    EXPECT_EQ(count, 1u);
}

TEST_F(SteeringRuntimeTest, addsRuleWithPortAddressTarget)
{
    IPv4Address targetAddress(testAddress1);
    SteeringTarget target(targetAddress, testPort1);
    IPv4Address address(testAddress2);

    auto result = runtime.addRule(Protocol::TCP4, 10, address, target);
    auto count = runtime.ruleCount();

    EXPECT_TRUE(result);
    EXPECT_EQ(count, 1u);
}

TEST_F(SteeringRuntimeTest, addsRuleException)
{
    IPv4Address address(testAddress1);
    SteeringTarget target(address, testPort1);

    runtime.addRule(Protocol::UDP4, target);

    EXPECT_THROW(runtime.addRule(Protocol::UDP4, target), DuplicatedTargetException);
}

TEST_F(SteeringRuntimeTest, removesRuleWithProtocolOnly)
{
    IPv4Address address(testAddress1);
    SteeringTarget target(address, testPort1);

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
    IPv4Address address(testAddress1);
    SteeringTarget target(address, testPort1);

    auto result = runtime.addRule(Protocol::UDP4, testPort2, target);
    auto count = runtime.ruleCount();
    auto resultRemove = runtime.removeRule(Protocol::UDP4, testPort2);
    auto finalCount = runtime.ruleCount();

    EXPECT_TRUE(result);
    EXPECT_EQ(count, 1u);
    EXPECT_TRUE(resultRemove);
    EXPECT_EQ(finalCount, 0u);
}

TEST_F(SteeringRuntimeTest, removesRuleWithProtocolAndPortAndAddress)
{
    IPv4Address targetAddress(testAddress1);
    SteeringTarget target(targetAddress, testPort1);
    IPv4Address address(testAddress2);

    auto result = runtime.addRule(Protocol::UDP4, testPort2, address, target);
    auto count = runtime.ruleCount();
    auto resultRemove = runtime.removeRule(Protocol::UDP4, testPort2, address);
    auto finalCount = runtime.ruleCount();

    EXPECT_TRUE(result);
    EXPECT_EQ(count, 1u);
    EXPECT_TRUE(resultRemove);
    EXPECT_EQ(finalCount, 0u);
}

TEST_F(SteeringRuntimeTest, removesRuleException)
{
    IPv4Address targetAddress(testAddress1);
    SteeringTarget target(targetAddress, testPort1);

    EXPECT_THROW(runtime.removeRule(Protocol::UDP6), InvalidProtocolException);
}

TEST_F(SteeringRuntimeTest, resetsRules)
{
    IPv4Address address(testAddress1);
    SteeringTarget target(address, testPort1);

    runtime.addRule(Protocol::UDP4, testPort2, target);
    auto ruleCount = runtime.ruleCount();
    runtime.reset();

    EXPECT_EQ(ruleCount, 1u);
    EXPECT_EQ(runtime.ruleCount(), 0u);
}

TEST_F(SteeringRuntimeTest, findsMatchingRule)
{
    IPv4Address address(testAddress1);
    SteeringTarget target(address, testPort4);
    runtime.addRule(Protocol::TCP4, testPort3, target);

    auto packet = createTcpPacket(testPort3);
    auto rule = runtime.ruleSearch(packet);

    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(rule->getTarget().getPort(), testPort4);
}
