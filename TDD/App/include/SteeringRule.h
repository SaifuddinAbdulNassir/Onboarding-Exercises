#pragma once

// Standard includes
#include <string>

// Library includes
#include <pcapplusplus/Packet.h>

// Project includes
#include "enums/Protocol.h"
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

    // Getters & Setters
    pcpp::IPv4Address getAddress() const {return address;}
    uint16_t getPort() const {return port;}
    Protocol getProtocol() const {return protocol;}
    SteeringTarget getTarget() const {return target;}

    // Fake Getters
    std::string getId() const;

    // Business logic
    bool matches(pcpp::Packet& packet) const;
};
