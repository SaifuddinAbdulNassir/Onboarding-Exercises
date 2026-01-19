#include "SteeringWorker.h"

// Library includes
#include <arpa/inet.h>
#include <pcapplusplus/IPv4Layer.h>
#include <pcapplusplus/TcpLayer.h>
#include <pcapplusplus/UdpLayer.h>

// Project includes
#include "exception/DropPacketException.h"

// Constructor

SteeringWorker::SteeringWorker(SteeringRuntime& runtime)
    : runtime(runtime) 
{
}

// Packet Processor

bool SteeringWorker::process(pcpp::Packet& packet)
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

// Packet diverter

void SteeringWorker::steer(pcpp::Packet& packet, SteeringTarget& target)
{
    auto ip = packet.getLayerOfType<pcpp::IPv4Layer>();
    if (!ip)
        throw InvalidArgumentException();

    if (auto* tcp = packet.getLayerOfType<pcpp::TcpLayer>())
        tcp->getTcpHeader()->portDst = htons(target.getPort());
    else if (auto* udp = packet.getLayerOfType<pcpp::UdpLayer>())
        udp->getUdpHeader()->portDst = htons(target.getPort());
    else
        throw InvalidProtocolException();

    packet.computeCalculateFields();

    if (target.getAddress() != pcpp::IPv4Address::Zero)
        ip->setDstIPv4Address(target.getAddress());
}
