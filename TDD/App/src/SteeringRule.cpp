#include "SteeringRule.h"

// Library includes
#include <pcapplusplus/IPv4Layer.h>
#include <pcapplusplus/TcpLayer.h>
#include <pcapplusplus/UdpLayer.h>

// Constructors

SteeringRule::SteeringRule(Protocol protocol, SteeringTarget target)
    : protocol(protocol), address(pcpp::IPv4Address::Zero), port(0), target(target) 
{
}

SteeringRule::SteeringRule(Protocol protocol, uint16_t port, SteeringTarget target)
    : protocol(protocol), address(pcpp::IPv4Address::Zero), port(port), target(target)
{
}

SteeringRule::SteeringRule(Protocol protocol, uint16_t port,
                           pcpp::IPv4Address address,
                           SteeringTarget target)
    : protocol(protocol), address(address), port(port), target(target)
{
}

// Getters

Protocol SteeringRule::getProtocol() const
{ 
    return protocol;
}

pcpp::IPv4Address SteeringRule::getAddress() const
{
    return address;
}

uint16_t SteeringRule::getPort() const
{
    return port;
}

SteeringTarget SteeringRule::getTarget() const
{
    return target;
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

    if (address != pcpp::IPv4Address::Zero)
        id += "-" + address.toString();

    return id;
}

// Match checking function

bool SteeringRule::matches(pcpp::Packet& packet) const
{
    if (ProtocolUtil::detect(packet) != protocol)
        return false;

    if (port != 0) 
    {
        if (auto tcp = packet.getLayerOfType<pcpp::TcpLayer>())
        {
            if (tcp->getDstPort() != port)
                return false;
        }
            
        if (auto udp = packet.getLayerOfType<pcpp::UdpLayer>())
        {
            if (udp->getDstPort() != port)
                return false;
        }
    }

    if (address != pcpp::IPv4Address::Zero)
    {
        auto ip = packet.getLayerOfType<pcpp::IPv4Layer>();
        if (!ip || ip->getDstIPv4Address() != address)
            return false;
    }

    return true;
}
