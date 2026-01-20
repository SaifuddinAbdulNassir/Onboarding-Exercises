#pragma once

// Standard includes
#include <string>

// Library includes
#include <pcapplusplus/Packet.h>

// Project includes
#include "enums/ProtocolTypes.h"
#include "ProtocolUtil.h"
#include "SteeringTarget.h"

using namespace std;
using namespace pcpp;

class SteeringRule 
{
    IPv4Address address;
    uint16_t port;
    Protocol protocol;
    SteeringTarget target;

  public:
    // Constructors
    SteeringRule(Protocol protocol, SteeringTarget target);
    SteeringRule(Protocol protocol, uint16_t port, SteeringTarget target);
    SteeringRule(Protocol protocol, uint16_t port,
                 IPv4Address address,
                 SteeringTarget target);

    // Getters
    IPv4Address getAddress() const;
    string getId() const;
    uint16_t getPort() const;
    Protocol getProtocol() const;
    SteeringTarget getTarget() const;

    // Packet matcher
    bool matches(Packet& packet) const;
};
