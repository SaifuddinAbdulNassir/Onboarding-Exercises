#include <gtest/gtest.h>

#include "SteeringRuntime.h"
#include "TestUtils.h"

class SteeringRuntimeTest : public ::testing::Test
{
  protected:
    SteeringRuntime runtime;
};

TEST_F(SteeringRuntimeTest, AddRemoveReset)
{
    pcpp::IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 53);

    EXPECT_EQ(0u, runtime.ruleCount());
    EXPECT_TRUE(runtime.addRule(Protocol::UDP4, target));
    EXPECT_EQ(1u, runtime.ruleCount());

    EXPECT_THROW(runtime.addRule(Protocol::UDP4, target), DuplicatedTargetException);

    EXPECT_TRUE(runtime.addRule(Protocol::TCP4, 10, target));
    EXPECT_EQ(2u, runtime.ruleCount());

    EXPECT_TRUE(runtime.removeRule(Protocol::UDP4));
    EXPECT_EQ(1u, runtime.ruleCount());
    EXPECT_TRUE(runtime.removeRule(Protocol::TCP4, 10));
    EXPECT_EQ(0u, runtime.ruleCount());

    EXPECT_TRUE(runtime.addRule(Protocol::UDP4, 50, target));
    EXPECT_EQ(1u, runtime.ruleCount());
    runtime.reset();
    EXPECT_EQ(0u, runtime.ruleCount());
}

TEST_F(SteeringRuntimeTest, RuleSearch)
{
    pcpp::IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 8080);
    runtime.addRule(Protocol::TCP4, 80, target);

    auto packet = createTcpPacket(80);
    auto rule = runtime.ruleSearch(packet);

    ASSERT_NE(nullptr, rule);
    EXPECT_EQ(8080, rule->getTarget().getPort());
}
