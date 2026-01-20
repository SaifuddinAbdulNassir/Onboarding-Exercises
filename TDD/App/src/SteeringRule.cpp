#include "SteeringRule.h"

// Library includes
#include <pcapplusplus/IPv4Layer.h>
#include <pcapplusplus/TcpLayer.h>
#include <pcapplusplus/UdpLayer.h>

using namespace std;
using namespace pcpp;

// Constructors

SteeringRule::SteeringRule(Protocol protocol, SteeringTarget target)
    : protocol(protocol), address(IPv4Address::Zero), port(0), target(target) 
{
}

SteeringRule::SteeringRule(Protocol protocol, uint16_t port, SteeringTarget target)
    : protocol(protocol), address(IPv4Address::Zero), port(port), target(target)
{
}

SteeringRule::SteeringRule(Protocol protocol, uint16_t port,
                           IPv4Address address,
                           SteeringTarget target)
    : protocol(protocol), address(address), port(port), target(target)
{
}

// Getters

IPv4Address SteeringRule::getAddress() const
{
    return address;
}

string SteeringRule::getId() const
{
    string id;

    switch (protocol) 
    {
        case Protocol::TCP4: id = "TCP4"; break;
        case Protocol::UDP4: id = "UDP4"; break;
        default: id = "UNKNOWN"; break;
    }

    if (port != 0)
        id += "-" + to_string(port);

    if (address != IPv4Address::Zero)
        id += "-" + address.toString();

    return id;
}

uint16_t SteeringRule::getPort() const
{
    return port;
}

Protocol SteeringRule::getProtocol() const
{ 
    return protocol;
}

SteeringTarget SteeringRule::getTarget() const
{
    return target;
}

// Packet matcher

bool SteeringRule::matches(Packet& packet) const
{
    if (ProtocolUtil::detect(packet) != protocol)
        return false;

    if (port != 0) 
    {
        if (auto tcp = packet.getLayerOfType<TcpLayer>())
        {
            if (tcp->getDstPort() != port)
                return false;
        }
            
        if (auto udp = packet.getLayerOfType<UdpLayer>())
        {
            if (udp->getDstPort() != port)
                return false;
        }
    }

    if (address != IPv4Address::Zero)
    {
        auto ip = packet.getLayerOfType<IPv4Layer>();
        if (!ip || ip->getDstIPv4Address() != address)
            return false;
    }

    return true;
}
