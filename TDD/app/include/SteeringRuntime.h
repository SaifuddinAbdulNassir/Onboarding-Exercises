#pragma once

// Standard includes
#include <memory>

// Library includes
#include <tbb/concurrent_unordered_map.h>

// Project includes
#include "SteeringRule.h"

namespace TDD
{

  class SteeringRuntime
  {
  protected:
    // Data
    tbb::concurrent_unordered_map<std::string, std::shared_ptr<SteeringRule>> rules;

  public:
    // Constructors & destructors
    SteeringRuntime();
    virtual ~SteeringRuntime();

    // Business logic
    bool addRule(Protocol protocol, SteeringTarget target);
    bool addRule(Protocol protocol, uint16_t port, SteeringTarget target);
    bool addRule(Protocol protocol, uint16_t port,
                 pcpp::IPv4Address address,
                 SteeringTarget target);
    bool removeRule(Protocol protocol);
    bool removeRule(Protocol protocol, uint16_t port);
    bool removeRule(Protocol protocol, uint16_t port, pcpp::IPv4Address address);
    void reset();
    size_t ruleCount() const;
    virtual std::shared_ptr<const SteeringRule> ruleSearch(pcpp::Packet &packet);
    static void validateProtocol(Protocol protocol);
  };

} // namespace TDD
