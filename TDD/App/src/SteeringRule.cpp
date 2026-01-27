#include "SteeringRule.h"

// Library includes
#include <pcapplusplus/IPv4Layer.h>
#include <pcapplusplus/TcpLayer.h>
#include <pcapplusplus/UdpLayer.h>

using namespace std;
using namespace pcpp;

bool matchesAddress(Packet& packet, const IPv4Address& address)
{
    if (address == IPv4Address::Zero)
        return true;
    auto* ip = packet.getLayerOfType<IPv4Layer>();
    return ip && ip->getDstIPv4Address() == address;
}

bool matchesPort(Packet& packet, uint16_t port)
{
    if (port == 0)
        return true;
    if (auto* tcp = packet.getLayerOfType<TcpLayer>())
        return tcp->getDstPort() == port;
    if (auto* udp = packet.getLayerOfType<UdpLayer>())
        return udp->getDstPort() == port;
    return false;
}

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

// Fake Getters

string SteeringRule::getId() const
{
    string id = protocol._to_string();

    if (port != 0)
        id += "-" + to_string(port);

    if (address != IPv4Address::Zero)
        id += "-" + address.toString();

    return id;
}

// Business logic

bool SteeringRule::matches(Packet& packet) const
{
    if (ProtocolUtil::detect(packet) != protocol)
        return false;

    if (!matchesAddress(packet, address))
        return false;

    if (!matchesPort(packet, port))
        return false;

    return true;
}
