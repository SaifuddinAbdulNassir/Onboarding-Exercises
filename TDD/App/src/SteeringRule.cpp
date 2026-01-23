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

// Fake Getters

string SteeringRule::getId() const
{
    string id;

    switch (protocol) 
    {
        case Protocol::TCP4: id = protocol._to_string(); break;
        case Protocol::UDP4: id = protocol._to_string(); break;
        default: id = "UNKNOWN"; break;
    }

    if (port != 0)
        id += "-" + to_string(port);

    if (address != IPv4Address::Zero)
        id += "-" + address.toString();

    return id;
}

// Business logic

bool SteeringRule::matches(Packet& packet) const
{
    bool protocolMatch = (ProtocolUtil::detect(packet) == protocol);

    bool addressMatch = (address == IPv4Address::Zero) ||
        ([&]() {
            auto ip = packet.getLayerOfType<IPv4Layer>();
            return ip && ip->getDstIPv4Address() == address;
        })();

    bool portMatch = (port == 0) ||
        ([&]() {
            if (auto tcp = packet.getLayerOfType<TcpLayer>())
                return tcp->getDstPort() == port;
            if (auto udp = packet.getLayerOfType<UdpLayer>())
                return udp->getDstPort() == port;
            return false;
        })();

    if (protocolMatch && addressMatch && portMatch)
        return true;
    else
        return false;
}
