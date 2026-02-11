// Library includes
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// Project includes
#include "exception/DropPacketException.h"
#include "exception/InvalidProtocolException.h"
#include "SteeringRuntimeMock.h"
#include "SteeringTest.h"
#include "SteeringWorker.h"
#include "util/TestUtils.h"

using ::testing::Return;
using ::testing::Throw;

using namespace pcpp;
using namespace std;

// Business logic

class SteeringWorkerTest : public SteeringTest
{
};

TEST_F(SteeringWorkerTest, processesValidRule)
{
    SteeringRuntime runtime;
    SteeringWorker worker(runtime);
    IPv4Address address(testAddress2);
    SteeringTarget target(address, testPort4);

    runtime.addRule(Protocol::TCP4, testPort3, testAddress1, target);
    auto packet = createTcpPacket(testPort3);

    EXPECT_TRUE(worker.process(packet));
}

TEST_F(SteeringWorkerTest, rejectsInvalidRule)
{
    SteeringRuntime runtime;
    SteeringWorker worker(runtime);
    IPv4Address address(testAddress2);
    SteeringTarget target(address, testPort4);

    runtime.addRule(Protocol::TCP4, testPort3, testAddress1, target);
    auto packet = createUdpPacket(22);

    EXPECT_FALSE(worker.process(packet));
}

TEST_F(SteeringWorkerTest, throwsDropPacketExceptionOnIcmpPacket)
{
    SteeringRuntime runtime;
    SteeringWorker worker(runtime);
    IPv4Address address(testAddress2);
    SteeringTarget target(address, testPort4);

    runtime.addRule(Protocol::TCP4, testPort3, testAddress1, target);
    auto packet = createIcmp4Packet();

    EXPECT_THROW(worker.process(packet), DropPacketException);
}

TEST_F(SteeringWorkerTest, steersValidTcpPacket)
{
    SteeringRuntime runtime;
    SteeringWorker worker(runtime);
    IPv4Address address(testAddress2);
    SteeringTarget target(address, testPort4);
    auto packet = createTcpPacket(testPort3);

    worker.steer(packet, target);
    auto tcp = packet.getLayerOfType<TcpLayer>();
    auto dstPort = tcp->getTcpHeader()->portDst;

    ASSERT_NE(tcp, nullptr);
    EXPECT_EQ(dstPort, target.getPort());
}

TEST_F(SteeringWorkerTest, steersValidUdpPacket)
{
    SteeringRuntime runtime;
    SteeringWorker worker(runtime);
    IPv4Address address(testAddress2);
    SteeringTarget target(address, testPort4);
    auto packet = createUdpPacket(testPort3);

    worker.steer(packet, target);
    auto udp = packet.getLayerOfType<UdpLayer>();
    auto dstPort = udp->getUdpHeader()->portDst;

    ASSERT_NE(udp, nullptr);
    EXPECT_EQ(dstPort, target.getPort());
}

TEST_F(SteeringWorkerTest, throwsInvalidArgumentExceptionForTcp6Packet)
{
    SteeringRuntime runtime;
    SteeringWorker worker(runtime);
    IPv4Address address(testAddress2);
    SteeringTarget target(address, testPort4);

    auto packet = createTcp6Packet(22);

    EXPECT_THROW(worker.steer(packet, target), InvalidArgumentException);
}

TEST_F(SteeringWorkerTest, throwsInvalidProtocolExceptionOnIcmpPacket)
{
    SteeringRuntime runtime;
    SteeringWorker worker(runtime);
    IPv4Address address(testAddress2);
    SteeringTarget target(address, testPort4);

    auto packet = createIcmp4Packet();

    EXPECT_THROW(worker.steer(packet, target), InvalidProtocolException);
}

TEST_F(SteeringWorkerTest, processesWithMockedRuntimeWithValidRule)
{
    SteeringRuntimeMock runtimeMock;
    SteeringWorker worker(runtimeMock);
    IPv4Address address(testAddress2);
    SteeringTarget target(address, testPort4);

    auto rule = make_shared<SteeringRule>(Protocol::TCP4, testPort3, target);
    auto packet = createTcpPacket(testPort3);
    EXPECT_CALL(runtimeMock, ruleSearch).WillOnce(Return(rule));

    EXPECT_TRUE(worker.process(packet));
}

TEST_F(SteeringWorkerTest, returnsFalseWhenRuntimeReturnsNullRule)
{
    SteeringRuntimeMock runtimeMock;
    SteeringWorker worker(runtimeMock);

    auto packet = createTcpPacket(testPort3);
    EXPECT_CALL(runtimeMock, ruleSearch).WillOnce(Return(shared_ptr<const SteeringRule>()));

    EXPECT_FALSE(worker.process(packet));
}

TEST_F(SteeringWorkerTest, throwsDropPacketExceptionFromMockedRuntime)
{
    SteeringRuntimeMock runtimeMock;
    SteeringWorker worker(runtimeMock);

    auto packet = createTcpPacket(testPort3);
    EXPECT_CALL(runtimeMock, ruleSearch).WillOnce(Throw(DropPacketException()));

    EXPECT_THROW(worker.process(packet), DropPacketException);
}

TEST_F(SteeringWorkerTest, throwsInvalidArgumentExceptionFromMockedRuntime)
{
    SteeringRuntimeMock runtimeMock;
    SteeringWorker worker(runtimeMock);

    auto packet = createTcpPacket(testPort3);
    EXPECT_CALL(runtimeMock, ruleSearch).WillOnce(Throw(InvalidArgumentException()));

    EXPECT_THROW(worker.process(packet), DropPacketException);
}
