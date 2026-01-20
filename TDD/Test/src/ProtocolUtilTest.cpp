// Library includes
#include <gtest/gtest.h>

// Project includes
#include "ProtocolUtil.h"
#include "TestUtils.h"

TEST(ProtocolUtilTest, detectTcp4)
{
    auto packet = createTcpPacket(80);

    EXPECT_EQ(Protocol::TCP4, ProtocolUtil::detect(packet)._value);
}

TEST(ProtocolUtilTest, detectTcp6)
{
    auto packet = createTcp6Packet(443);

    EXPECT_EQ(Protocol::TCP6, ProtocolUtil::detect(packet)._value);
}

TEST(ProtocolUtilTest, detectUdp4)
{
    auto packet = createUdpPacket(53);

    EXPECT_EQ(Protocol::UDP4, ProtocolUtil::detect(packet)._value);
}

TEST(ProtocolUtilTest, detectUdp6)
{
    auto packet = createUdp6Packet(53);

    EXPECT_EQ(Protocol::UDP6, ProtocolUtil::detect(packet)._value);
}

TEST(ProtocolUtilTest, detectUnknown)
{
    auto packet = createIcmp4Packet();
    
    EXPECT_EQ(Protocol::UNKNOWN, ProtocolUtil::detect(packet)._value);
}