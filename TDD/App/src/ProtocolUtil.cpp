#include "ProtocolUtil.h"

// Library includes
#include <pcapplusplus/IPv4Layer.h>
#include <pcapplusplus/IPv6Layer.h>
#include <pcapplusplus/TcpLayer.h>
#include <pcapplusplus/UdpLayer.h>

Protocol ProtocolUtil::detect(pcpp::Packet& packet)
{
    if (packet.isPacketOfType(pcpp::TCP)) 
    {
        if(packet.isPacketOfType(pcpp::IPv4))
            return Protocol::TCP4;
        else if(packet.isPacketOfType(pcpp::IPv6))
            return Protocol::TCP6;
    }

    if (packet.isPacketOfType(pcpp::UDP)) 
    {
        if(packet.isPacketOfType(pcpp::IPv4))
            return Protocol::UDP4;
        if(packet.isPacketOfType(pcpp::IPv6))
            return Protocol::UDP6;
    }

    return Protocol::UNKNOWN;
}
