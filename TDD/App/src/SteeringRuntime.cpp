#include "SteeringRuntime.h"

using namespace std;
using namespace pcpp;

// Validator

static void validateProtocol(Protocol protocol)
{
    if(protocol._value != Protocol::TCP4 && protocol._value != Protocol::UDP4)
        throw InvalidProtocolException();
}

// Rule Modifiers

bool SteeringRuntime::addRule(Protocol protocol, SteeringTarget target)
{
    return addRule(protocol, 0, IPv4Address::Zero, target);
}

bool SteeringRuntime::addRule(Protocol protocol, uint16_t port, SteeringTarget target)
{
    return addRule(protocol, port, IPv4Address::Zero, target);
}

bool SteeringRuntime::addRule(Protocol protocol, uint16_t port,
                              IPv4Address address,
                              SteeringTarget target)
{
    validateProtocol(protocol);

    for (const auto& [_, rule] : rules)
    {
        if(rule->getProtocol() == protocol && rule->getTarget() == target)
            throw DuplicatedTargetException();
    }
        
    auto rule = make_shared<SteeringRule>(protocol, port, address, target);
    auto id = rule->getId();

    if(rules.count(id))
        return false;

    rules[id] = rule;
    return true;
}

bool SteeringRuntime::removeRule(Protocol protocol)
{
    return removeRule(protocol, 0, IPv4Address::Zero);
}

bool SteeringRuntime::removeRule(Protocol protocol, uint16_t port)
{
    return removeRule(protocol, port, IPv4Address::Zero);
}

bool SteeringRuntime::removeRule(Protocol protocol, uint16_t port,
                                 IPv4Address address)
{
    validateProtocol(protocol);

    SteeringRule tmp(protocol, port, address,
                     SteeringTarget(IPv4Address("1.1.1.1"), 1));
    auto id = tmp.getId();

    return rules.unsafe_erase(id) > 0;
}

// Reseter

void SteeringRuntime::reset()
{
    rules.clear();
}

// Rule counter

size_t SteeringRuntime::ruleCount() const
{
    return rules.size();
}

// Rule searcher

shared_ptr<const SteeringRule>
SteeringRuntime::ruleSearch(Packet& packet)
{
    auto proto = ProtocolUtil::detect(packet);
    validateProtocol(proto);

    for (const auto& [_, rule] : rules)
    {
        if(rule->matches(packet))
            return rule;
    }

    return nullptr;
}
