#include "SteeringTarget.h"

using namespace pcpp;

// Constructor

SteeringTarget::SteeringTarget(IPv4Address address, uint16_t port)
{
    if(address == IPv4Address::Zero || port == 0)
        throw InvalidArgumentException();

    this->address = address;
    this->port = port;
}

// Getters and Setters

void SteeringTarget::setAddress(IPv4Address address)
{
    if(address == IPv4Address::Zero)
        throw InvalidArgumentException();

    this->address = address;
}

void SteeringTarget::setPort(uint16_t port)
{
    if(port == 0)
        throw InvalidArgumentException();

    this->port = port;
}

// Operators

bool SteeringTarget::operator==(const SteeringTarget& other) const
{
    return address == other.address && port == other.port;
}
