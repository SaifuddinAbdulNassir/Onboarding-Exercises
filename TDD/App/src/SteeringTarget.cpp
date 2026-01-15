#include "SteeringTarget.h"

SteeringTarget::SteeringTarget(pcpp::IPv4Address address, uint16_t port)
{
    if (address == pcpp::IPv4Address::Zero || port == 0)
    {
        throw InvalidArgumentException();
    }

    this->address = address;
    this->port = port;
}

pcpp::IPv4Address SteeringTarget::getAddress() const
{
    return address;
}

void SteeringTarget::setAddress(pcpp::IPv4Address address)
{
    if (address == pcpp::IPv4Address::Zero)
    {
        throw InvalidArgumentException();
    }

    this->address = address;
}

uint16_t SteeringTarget::getPort() const
{
    return port;
}

void SteeringTarget::setPort(uint16_t port)
{
    if (port == 0)
    {
        throw InvalidArgumentException();
    }
    this->port = port;
}

bool SteeringTarget::operator==(const SteeringTarget& other) const
{
    return address == other.address && port == other.port;
}
