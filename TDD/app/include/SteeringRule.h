#pragma once

// Standard includes
#include <string>

// Library includes
#include <pcapplusplus/IpAddress.h>

// Project includes
#include "enums/Protocol.h"
#include "SteeringTarget.h"

namespace pcpp
{
  class Packet;
}

namespace TDD
{

  class SteeringRule
  {
  private:
    // Data
    pcpp::IPv4Address address;
    uint16_t port;
    Protocol protocol;
    SteeringTarget target;

    // Helper functions
    bool matchesAddress(pcpp::Packet &packet, const pcpp::IPv4Address &address) const;
    bool matchesPort(pcpp::Packet &packet, uint16_t port) const;

  public:
    // Constructors & destructors
    SteeringRule(Protocol protocol, SteeringTarget target);
    SteeringRule(Protocol protocol, uint16_t port, SteeringTarget target);
    SteeringRule(Protocol protocol, uint16_t port,
                 pcpp::IPv4Address address,
                 SteeringTarget target);
    virtual ~SteeringRule();

    // Getters & setters
    const pcpp::IPv4Address &getAddress() const { return address; }
    uint16_t getPort() const { return port; }
    const Protocol &getProtocol() const { return protocol; }
    const SteeringTarget &getTarget() const { return target; }

    // Fake getters
    std::string getId() const;

    // Business logic
    bool matches(pcpp::Packet &packet) const;
  };

} // namespace TDD
