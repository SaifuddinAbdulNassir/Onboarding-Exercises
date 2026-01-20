#pragma once

// Standard includes
#include <string>

// Library includes
#include <pcapplusplus/Packet.h>

// Project includes
#include "enums/ProtocolTypes.h"
#include "ProtocolUtil.h"
#include "SteeringTarget.h"

class SteeringRule 
{
    pcpp::IPv4Address address;
    uint16_t port;
    Protocol protocol;
    SteeringTarget target;

  public:
    // Constructors
    SteeringRule(Protocol protocol, SteeringTarget target);
    SteeringRule(Protocol protocol, uint16_t port, SteeringTarget target);
    SteeringRule(Protocol protocol, uint16_t port,
                 pcpp::IPv4Address address,
                 SteeringTarget target);

    // Getters
    pcpp::IPv4Address getAddress() const;
    std::string getId() const;
    uint16_t getPort() const;
    Protocol getProtocol() const;
    SteeringTarget getTarget() const;

    // Packet matcher
    bool matches(pcpp::Packet& packet) const;
};
