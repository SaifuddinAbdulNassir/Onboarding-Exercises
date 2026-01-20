#pragma once

// Standard includes
#include <map>
#include <memory>
#include <tbb/concurrent_unordered_map.h>

// Project includes
#include "exception/DuplicatedTargetException.h"
#include "exception/InvalidProtocolException.h"
#include "SteeringRule.h"

class SteeringRuntime 
{
  protected:
    tbb::concurrent_unordered_map<std::string, std::shared_ptr<SteeringRule>> rules;

  public:
    // Destructor
    virtual ~SteeringRuntime() = default;

    // Rule Modifiers
    bool addRule(Protocol protocol, SteeringTarget target);
    bool addRule(Protocol protocol, uint16_t port, SteeringTarget target);
    bool addRule(Protocol protocol, uint16_t port,
                 pcpp::IPv4Address address,
                 SteeringTarget target);
    bool removeRule(Protocol protocol);
    bool removeRule(Protocol protocol, uint16_t port);
    bool removeRule(Protocol protocol, uint16_t port, pcpp::IPv4Address address);
    
    // Reseter
    void reset();

    // Rule Counter
    size_t ruleCount() const;

    // Rule Searcher
    virtual std::shared_ptr<const SteeringRule> ruleSearch(pcpp::Packet& packet);
};
