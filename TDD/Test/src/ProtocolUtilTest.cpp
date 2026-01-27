// Library includes
#include <gtest/gtest.h>

// Project includes
#include "ProtocolUtil.h"
#include "TestUtils.h"

// // Protocol detector

TEST(ProtocolUtilTest, detectsTcp4)
{
    auto packet = createTcpPacket(80);

    EXPECT_EQ(ProtocolUtil::detect(packet)._value, Protocol::TCP4);
}

TEST(ProtocolUtilTest, detectsTcp6)
{
    auto packet = createTcp6Packet(443);

    EXPECT_EQ(ProtocolUtil::detect(packet)._value, Protocol::TCP6);
}

TEST(ProtocolUtilTest, detectsUdp4)
{
    auto packet = createUdpPacket(53);

    EXPECT_EQ(ProtocolUtil::detect(packet)._value, Protocol::UDP4);
}

TEST(ProtocolUtilTest, detectsUdp6)
{
    auto packet = createUdp6Packet(53);

    EXPECT_EQ(ProtocolUtil::detect(packet)._value, Protocol::UDP6);
}

TEST(ProtocolUtilTest, detectsUnknown)
{
    auto packet = createIcmp4Packet();
    
    EXPECT_EQ(ProtocolUtil::detect(packet)._value, Protocol::UNKNOWN);
}
