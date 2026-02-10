// Library includes
#include <arpa/inet.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// Project includes
#include "exception/DropPacketException.h"
#include "exception/InvalidProtocolException.h"
#include "SteeringRuntimeMock.h"
#include "SteeringWorker.h"
#include "TestUtils.h"

using ::testing::Return;
using ::testing::Throw;

using namespace pcpp;
using namespace std;

// Business logic

TEST(SteeringWorkerTest, processesValidRule)
{
    SteeringRuntime runtime;
    SteeringWorker worker(runtime);
    IPv4Address address(TEST_ADDRESS_2);
    SteeringTarget target(address, TEST_PORT_4);

    runtime.addRule(Protocol::TCP4, TEST_PORT_3, IPv4Address(TEST_ADDRESS_1), target);
    auto packet = createTcpPacket(TEST_PORT_3);
    EXPECT_TRUE(worker.process(packet));
}

TEST(SteeringWorkerTest, rejectsInvalidRule)
{
    SteeringRuntime runtime;
    SteeringWorker worker(runtime);
    IPv4Address address(TEST_ADDRESS_2);
    SteeringTarget target(address, TEST_PORT_4);

    runtime.addRule(Protocol::TCP4, TEST_PORT_3, IPv4Address(TEST_ADDRESS_1), target);
    auto packet = createUdpPacket(22);

    EXPECT_FALSE(worker.process(packet));
}

TEST(SteeringWorkerTest, handlesRuleProcessingExceptions)
{
    SteeringRuntime runtime;
    SteeringWorker worker(runtime);
    IPv4Address address(TEST_ADDRESS_2);
    SteeringTarget target(address, TEST_PORT_4);

    runtime.addRule(Protocol::TCP4, TEST_PORT_3, IPv4Address(TEST_ADDRESS_1), target);
    auto packet = createIcmp4Packet();

    EXPECT_THROW(worker.process(packet), DropPacketException);
}

TEST(SteeringWorkerTest, steersValidTcpPacket)
{
    SteeringRuntime runtime;
    SteeringWorker worker(runtime);
    IPv4Address address(TEST_ADDRESS_2);
    SteeringTarget target(address, TEST_PORT_4);

    auto packet = createTcpPacket(TEST_PORT_3);
    worker.steer(packet, target);
    auto tcp = packet.getLayerOfType<TcpLayer>();
    auto dstPort = tcp->getTcpHeader()->portDst;

    ASSERT_NE(tcp, nullptr);
    EXPECT_EQ(dstPort, htons(target.getPort()));
}

TEST(SteeringWorkerTest, steersValidUdpPacket)
{
    SteeringRuntime runtime;
    SteeringWorker worker(runtime);
    IPv4Address address(TEST_ADDRESS_2);
    SteeringTarget target(address, TEST_PORT_4);

    auto packet = createUdpPacket(TEST_PORT_3);
    worker.steer(packet, target);
    auto udp = packet.getLayerOfType<UdpLayer>();
    auto dstPort = udp->getUdpHeader()->portDst;

    ASSERT_NE(udp, nullptr);
    EXPECT_EQ(dstPort, htons(target.getPort()));
}

TEST(SteeringWorkerTest, throwsInvalidArgumentExceptionForInvalidPacket)
{
    SteeringRuntime runtime;
    SteeringWorker worker(runtime);
    IPv4Address address(TEST_ADDRESS_2);
    SteeringTarget target(address, TEST_PORT_4);

    auto packet = createTcp6Packet(22);

    EXPECT_THROW(worker.steer(packet, target), InvalidArgumentException);
}

TEST(SteeringWorkerTest, throwsInvalidProtocolException)
{
    SteeringRuntime runtime;
    SteeringWorker worker(runtime);
    IPv4Address address(TEST_ADDRESS_2);
    SteeringTarget target(address, TEST_PORT_4);

    auto packet = createIcmp4Packet();

    EXPECT_THROW(worker.steer(packet, target), InvalidProtocolException);
}

TEST(SteeringWorkerTest, processesWithMockedRuntimeWithValidRule)
{
    SteeringRuntimeMock runtimeMock;
    SteeringWorker worker(runtimeMock);
    IPv4Address address(TEST_ADDRESS_2);
    SteeringTarget target(address, TEST_PORT_4);
    auto rule = make_shared<SteeringRule>(Protocol::TCP4, TEST_PORT_3, target);

    auto packet = createTcpPacket(TEST_PORT_3);
    EXPECT_CALL(runtimeMock, ruleSearch).WillOnce(Return(rule));

    EXPECT_TRUE(worker.process(packet));
}

TEST(SteeringWorkerTest, processesWithMockedRuntimeWithNullRule)
{
    SteeringRuntimeMock runtimeMock;
    SteeringWorker worker(runtimeMock);

    auto packet = createTcpPacket(TEST_PORT_3);
    EXPECT_CALL(runtimeMock, ruleSearch).WillOnce(Return(shared_ptr<const SteeringRule>()));

    EXPECT_FALSE(worker.process(packet));
}

TEST(SteeringWorkerTest, throwsDropPacketExceptionFromMockedRuntime)
{
    SteeringRuntimeMock runtimeMock;
    SteeringWorker worker(runtimeMock);

    auto packet = createTcpPacket(TEST_PORT_3);
    EXPECT_CALL(runtimeMock, ruleSearch).WillOnce(Throw(DropPacketException()));

    EXPECT_THROW(worker.process(packet), DropPacketException);
}

TEST(SteeringWorkerTest, throwsInvalidArgumentExceptionFromMockedRuntime)
{
    SteeringRuntimeMock runtimeMock;
    SteeringWorker worker(runtimeMock);

    auto packet = createTcpPacket(TEST_PORT_3);
    EXPECT_CALL(runtimeMock, ruleSearch).WillOnce(Throw(InvalidArgumentException()));

    EXPECT_THROW(worker.process(packet), DropPacketException);
}
