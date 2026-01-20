#pragma once

// Library includes
#include <pcapplusplus/IpAddress.h>

// Project includes
#include "exception/InvalidArgumentException.h"

using namespace pcpp;

class SteeringTarget 
{
    IPv4Address address;
    uint16_t port;

  public:
    // Constructor
    SteeringTarget(IPv4Address address, uint16_t port);

    // Getters and Setters
    IPv4Address getAddress() const;
    uint16_t getPort() const;
    void setAddress(IPv4Address address);
    void setPort(uint16_t port);

    // Equals operator
    bool operator==(const SteeringTarget& other) const;
};
