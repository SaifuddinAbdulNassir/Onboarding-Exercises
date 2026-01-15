#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "exception/DropPacketException.h"
#include "SteeringRuntimeMock.h"
#include "SteeringWorker.h"
#include "TestUtils.h"

using ::testing::Return;

TEST(SteeringWorkerTest, ProcessWithRuntime)
{
    SteeringRuntime runtime;
    SteeringWorker worker(runtime);

    pcpp::IPv4Address address("10.0.0.1");
    SteeringTarget target(address, 8080);
    runtime.addRule(Protocol::TCP4, 80, pcpp::IPv4Address("8.8.8.8"), target);
    
    auto packet = createTcpPacket(80);
    EXPECT_TRUE(worker.process(packet));

    auto tcp = packet.getLayerOfType<pcpp::TcpLayer>();
    ASSERT_NE(nullptr, tcp);
    EXPECT_EQ(8080, tcp->getDstPort());

    auto ip4 = packet.getLayerOfType<pcpp::IPv4Layer>();
    EXPECT_EQ(address, ip4->getDstIPv4Address());

    runtime.addRule(Protocol::UDP4, 80, pcpp::IPv4Address("8.8.8.8"), target);
    packet = createUdpPacket(80);
    EXPECT_TRUE(worker.process(packet));

    packet = createUdpPacket(22);
    EXPECT_FALSE(worker.process(packet));
    
    packet = createIcmp4Packet();
    EXPECT_THROW(worker.process(packet), DropPacketException);
}

TEST(SteeringWorkerTest, SteerWithRuntime)
{
    SteeringRuntime runtime;
    SteeringWorker worker(runtime);

    pcpp::IPv4Address address("10.0.0.1");
    SteeringTarget target(address, 8080);

    auto packet = createTcp6Packet(22);
    EXPECT_THROW(worker.steer(packet, target), InvalidArgumentException);

    packet = createIcmp4Packet();
    EXPECT_THROW(worker.steer(packet, target), InvalidProtocolException);
}


TEST(SteeringWorkerTest, ProcessWithMockedRuntime)
{
    SteeringRuntimeMock runtimeMock;
    SteeringWorker worker(runtimeMock);

    pcpp::IPv4Address address("8.8.8.8");
    SteeringTarget target(address, 8080);
    auto rule = std::make_shared<SteeringRule>(
        Protocol::TCP4, 80, target
    );

    auto packet = createTcpPacket(80);

    EXPECT_CALL(runtimeMock, ruleSearch)
        .WillOnce(Return(rule));

    EXPECT_TRUE(worker.process(packet));

    auto tcp = packet.getLayerOfType<pcpp::TcpLayer>();
    ASSERT_NE(nullptr, tcp);
    EXPECT_EQ(8080, tcp->getDstPort());

    auto ip4 = packet.getLayerOfType<pcpp::IPv4Layer>();
    EXPECT_EQ(address, ip4->getDstIPv4Address());
}