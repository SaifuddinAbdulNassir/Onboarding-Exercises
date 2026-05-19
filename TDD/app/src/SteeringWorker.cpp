#include "SteeringWorker.h"

// Library includes
#include <pcapplusplus/IPv4Layer.h>
#include <pcapplusplus/Packet.h>
#include <pcapplusplus/TcpLayer.h>
#include <pcapplusplus/UdpLayer.h>

// Project includes
#include "exception/DropPacketException.h"
#include "exception/InvalidProtocolException.h"

using namespace pcpp;
using namespace TDD;

// Constructors & destructors

SteeringWorker::SteeringWorker(SteeringRuntime &runtime)
    : runtime(runtime)
{
}

SteeringWorker::~SteeringWorker()
{
}

// Business logic

bool SteeringWorker::process(Packet &packet)
{
    try
    {
        // Search for a matching rule
        auto rule = runtime.ruleSearch(packet);
        if (!rule)
            return false;

        // Steer the packet according to the rule's target
        auto target = rule->getTarget();
        steer(packet, target);
        return true;
    }
    catch (...)
    {
        throw DropPacketException();
    }
}

void SteeringWorker::steer(Packet &packet, SteeringTarget &target)
{
    auto ip = packet.getLayerOfType<IPv4Layer>();
    if (!ip)
        throw InvalidArgumentException();

    // Steer port
    if (auto *tcp = packet.getLayerOfType<TcpLayer>())
        tcp->getTcpHeader()->portDst = target.getPort();
    else if (auto *udp = packet.getLayerOfType<UdpLayer>())
        udp->getUdpHeader()->portDst = target.getPort();
    else
        throw InvalidProtocolException();

    // Steer address
    if (target.getAddress() != IPv4Address::Zero)
        ip->setDstIPv4Address(target.getAddress());

    packet.computeCalculateFields();
}
