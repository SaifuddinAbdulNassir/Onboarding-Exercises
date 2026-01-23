// Library includes
#include <arpa/inet.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// Project includes
#include "exception/DropPacketException.h"
#include "SteeringRuntimeMock.h"
#include "SteeringWorker.h"
#include "TestUtils.h"

using ::testing::Return;
using ::testing::Throw;

// Business logic tests

TEST(SteeringWorkerTest, processesValidRule)
{
    SteeringRuntime runtime;
    SteeringWorker worker(runtime);
    pcpp::IPv4Address address("10.0.0.1");
    SteeringTarget target(address, 8080);

    runtime.addRule(Protocol::TCP4, 80, pcpp::IPv4Address("8.8.8.8"), target);
    auto packet = createTcpPacket(80);

    EXPECT_TRUE(worker.process(packet));
}

TEST(SteeringWorkerTest, rejectsInvalidRule)
{
    SteeringRuntime runtime;
    SteeringWorker worker(runtime);
    pcpp::IPv4Address address("10.0.0.1");
    SteeringTarget target(address, 8080);

    runtime.addRule(Protocol::TCP4, 80, pcpp::IPv4Address("8.8.8.8"), target);
    auto packet = createUdpPacket(22);

    EXPECT_FALSE(worker.process(packet));
}

TEST(SteeringWorkerTest, handlesRuleProcessingExceptions)
{
    SteeringRuntime runtime;
    SteeringWorker worker(runtime);
    pcpp::IPv4Address address("10.0.0.1");
    SteeringTarget target(address, 8080);

    runtime.addRule(Protocol::TCP4, 80, pcpp::IPv4Address("8.8.8.8"), target);
    auto packet = createIcmp4Packet();

    EXPECT_THROW(worker.process(packet), DropPacketException);
}

TEST(SteeringWorkerTest, steersValidTcpPacket)
{
    SteeringRuntime runtime;
    SteeringWorker worker(runtime);
    pcpp::IPv4Address address("10.0.0.1");
    SteeringTarget target(address, 8080);

    auto packet = createTcpPacket(80);
    worker.steer(packet, target);
    auto tcp = packet.getLayerOfType<pcpp::TcpLayer>();

    ASSERT_NE(tcp, nullptr);
    EXPECT_EQ(tcp->getTcpHeader()->portDst, htons(target.getPort()));
}

TEST(SteeringWorkerTest, steersValidUdpPacket)
{
    SteeringRuntime runtime;
    SteeringWorker worker(runtime);
    pcpp::IPv4Address address("10.0.0.1");
    SteeringTarget target(address, 8080);

    auto packet = createUdpPacket(80);
    worker.steer(packet, target);
    auto udp = packet.getLayerOfType<pcpp::UdpLayer>();

    ASSERT_NE(udp, nullptr);
    EXPECT_EQ(udp->getUdpHeader()->portDst, htons(target.getPort()));
}

TEST(SteeringWorkerTest, throwsInvalidArgumentExceptionForInvalidPacket)
{
    SteeringRuntime runtime;
    SteeringWorker worker(runtime);
    pcpp::IPv4Address address("10.0.0.1");
    SteeringTarget target(address, 8080);

    auto packet = createTcp6Packet(22);

    EXPECT_THROW(worker.steer(packet, target), InvalidArgumentException);
}

TEST(SteeringWorkerTest, throwsInvalidProtocolException)
{
    SteeringRuntime runtime;
    SteeringWorker worker(runtime);
    pcpp::IPv4Address address("10.0.0.1");
    SteeringTarget target(address, 8080);
    
    auto packet = createIcmp4Packet();

    EXPECT_THROW(worker.steer(packet, target), InvalidProtocolException);
}

TEST(SteeringWorkerTest, processesWithMockedRuntimeWithValidRule)
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
}

TEST(SteeringWorkerTest, processesWithMockedRuntimeWithNullRule)
{
    SteeringRuntimeMock runtimeMock;
    SteeringWorker worker(runtimeMock);

    auto packet = createTcpPacket(80);
    EXPECT_CALL(runtimeMock, ruleSearch)
        .WillOnce(Return(std::shared_ptr<const SteeringRule>()));

    EXPECT_FALSE(worker.process(packet));
}

TEST(SteeringWorkerTest, throwsDropPacketExceptionFromMockedRuntime)
{
    SteeringRuntimeMock runtimeMock;
    SteeringWorker worker(runtimeMock);

    auto packet = createTcpPacket(80);
    EXPECT_CALL(runtimeMock, ruleSearch)
        .WillOnce(Throw(DropPacketException()));

    EXPECT_THROW(worker.process(packet), DropPacketException);
}

TEST(SteeringWorkerTest, throwsInvalidArgumentExceptionFromMockedRuntime)
{
    SteeringRuntimeMock runtimeMock;
    SteeringWorker worker(runtimeMock);

    auto packet = createTcpPacket(80);
    EXPECT_CALL(runtimeMock, ruleSearch)
        .WillOnce(Throw(InvalidArgumentException()));

    EXPECT_THROW(worker.process(packet), DropPacketException);
}
