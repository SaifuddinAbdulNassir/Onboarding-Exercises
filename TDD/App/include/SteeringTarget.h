#pragma once

// Library includes
#include <pcapplusplus/IpAddress.h>

// Project includes
#include "exception/InvalidArgumentException.h"

namespace TDD
{

  class SteeringTarget
  {
  private:
    pcpp::IPv4Address address;
    uint16_t port;

  public:
    // Constructors & destructors
    SteeringTarget(pcpp::IPv4Address address, uint16_t port);
    virtual ~SteeringTarget();

    // Getters and Setters
    pcpp::IPv4Address getAddress() const { return address; }
    uint16_t getPort() const { return port; }
    void setAddress(pcpp::IPv4Address address);
    void setPort(uint16_t port);

    // Relational operators
    bool operator==(const SteeringTarget &other) const;
  };

} // namespace TDD
