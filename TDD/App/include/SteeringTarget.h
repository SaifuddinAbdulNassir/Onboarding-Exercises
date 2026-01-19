#pragma once

// Library includes
#include <pcapplusplus/IpAddress.h>

// Project includes
#include "exception/InvalidArgumentException.h"

class SteeringTarget 
{
    pcpp::IPv4Address address;
    uint16_t port;

  public:
    SteeringTarget(pcpp::IPv4Address address, uint16_t port);

    pcpp::IPv4Address getAddress() const;
    void setAddress(pcpp::IPv4Address address);

    uint16_t getPort() const;
    void setPort(uint16_t port);

    bool operator==(const SteeringTarget& other) const;
};
