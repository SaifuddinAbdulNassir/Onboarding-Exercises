#pragma once

#include <string>

#include <pcapplusplus/Packet.h>

#include "enums/ProtocolEnum.h"
#include "ProtocolUtil.h"
#include "SteeringTarget.h"


class SteeringRule 
{
    Protocol protocol;
    pcpp::IPv4Address address;
    uint16_t port;
    SteeringTarget target;

  public:
    SteeringRule(Protocol protocol, SteeringTarget target);
    SteeringRule(Protocol protocol, uint16_t port, SteeringTarget target);
    SteeringRule(Protocol protocol, uint16_t port,
                 pcpp::IPv4Address address,
                 SteeringTarget target);

    Protocol getProtocol() const;
    pcpp::IPv4Address getAddress() const;
    uint16_t getPort() const;
    SteeringTarget getTarget() const;
    
    std::string getId() const;
    bool matches(pcpp::Packet& packet) const;
};
