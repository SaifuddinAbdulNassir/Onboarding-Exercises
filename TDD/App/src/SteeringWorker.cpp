#include "SteeringWorker.h"

// Library includes
#include <arpa/inet.h>
#include <pcapplusplus/IPv4Layer.h>
#include <pcapplusplus/TcpLayer.h>
#include <pcapplusplus/UdpLayer.h>

// Project includes
#include "exception/DropPacketException.h"

using namespace pcpp;

// Constructor

SteeringWorker::SteeringWorker(SteeringRuntime& runtime)
    : runtime(runtime) 
{
}

// Business logic

bool SteeringWorker::process(Packet& packet)
{
    try 
    {
        auto rule = runtime.ruleSearch(packet);
        if (!rule)
            return false;

        auto target = rule->getTarget();
        steer(packet, target);
        return true;
    }
    catch (...) 
    {
        throw DropPacketException();
    }
}

void SteeringWorker::steer(Packet& packet, SteeringTarget& target)
{
    auto ip = packet.getLayerOfType<IPv4Layer>();
    if (!ip)
        throw InvalidArgumentException();

    if (auto* tcp = packet.getLayerOfType<TcpLayer>())
        tcp->getTcpHeader()->portDst = htons(target.getPort());
    else if (auto* udp = packet.getLayerOfType<UdpLayer>())
        udp->getUdpHeader()->portDst = htons(target.getPort());
    else
        throw InvalidProtocolException();

    packet.computeCalculateFields();

    if (target.getAddress() != IPv4Address::Zero)
        ip->setDstIPv4Address(target.getAddress());
}
