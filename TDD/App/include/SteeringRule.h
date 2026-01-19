#pragma once

// Standard includes
#include <string>

// Library includes
#include <pcapplusplus/Packet.h>

// Project includes
#include "enums/ProtocolEnum.h"
#include "ProtocolUtil.h"
#include "SteeringTarget.h"

using namespace std;

class SteeringRule 
{
    pcpp::IPv4Address address;
    uint16_t port;
    Protocol protocol;
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
    
    string getId() const;
    bool matches(pcpp::Packet& packet) const;
};
