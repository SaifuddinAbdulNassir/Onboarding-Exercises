#include "ProtocolUtil.h"

// Library includes
#include <pcapplusplus/IPv4Layer.h>
#include <pcapplusplus/IPv6Layer.h>
#include <pcapplusplus/TcpLayer.h>
#include <pcapplusplus/UdpLayer.h>

using namespace pcpp;

// Protocol detector

Protocol ProtocolUtil::detect(Packet& packet)
{
    if (packet.isPacketOfType(TCP)) 
    {
        if(packet.isPacketOfType(IPv4))
            return Protocol::TCP4;
        else if(packet.isPacketOfType(IPv6))
            return Protocol::TCP6;
    }

    if (packet.isPacketOfType(UDP)) 
    {
        if(packet.isPacketOfType(IPv4))
            return Protocol::UDP4;
        if(packet.isPacketOfType(IPv6))
            return Protocol::UDP6;
    }

    return Protocol::UNKNOWN;
}
