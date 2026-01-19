#pragma once

// Library includes
#include <pcapplusplus/EthLayer.h>
#include <pcapplusplus/IcmpLayer.h>
#include <pcapplusplus/IPv4Layer.h>
#include <pcapplusplus/IPv6Layer.h>
#include <pcapplusplus/Packet.h>
#include <pcapplusplus/TcpLayer.h>
#include <pcapplusplus/UdpLayer.h>

inline pcpp::Packet createTcpPacket(uint16_t dstPort)
{
    pcpp::Packet packet(100);

     auto eth = new pcpp::EthLayer(
        pcpp::MacAddress("aa:aa:aa:aa:aa:aa"),
        pcpp::MacAddress("bb:bb:bb:bb:bb:bb"),
        PCPP_ETHERTYPE_IP
    );
    auto ip  = new pcpp::IPv4Layer(
        pcpp::IPv4Address("10.0.0.1"),
        pcpp::IPv4Address("8.8.8.8")
    );
    auto tcp = new pcpp::TcpLayer(12345, dstPort);

    packet.addLayer(eth);
    packet.addLayer(ip);
    packet.addLayer(tcp);
    packet.computeCalculateFields();

    return packet;
}

inline pcpp::Packet createTcp6Packet(uint16_t dstPort)
{
    pcpp::Packet packet(100);

     auto* eth = new pcpp::EthLayer(
        pcpp::MacAddress("aa:bb:cc:dd:ee:ff"),
        pcpp::MacAddress("11:22:33:44:55:66"),
        PCPP_ETHERTYPE_IPV6
    );

    auto* ip6 = new pcpp::IPv6Layer(
        pcpp::IPv6Address("2001:db8::1"),
        pcpp::IPv6Address("2001:db8::2")
    );

    auto* tcp = new pcpp::TcpLayer(12345, dstPort);

    packet.addLayer(eth);
    packet.addLayer(ip6);
    packet.addLayer(tcp);
    packet.computeCalculateFields();

    return packet;
}

inline pcpp::Packet createUdpPacket(uint16_t dstPort)
{
    pcpp::Packet packet(100);

    auto eth = new pcpp::EthLayer(
        pcpp::MacAddress("aa:aa:aa:aa:aa:aa"),
        pcpp::MacAddress("bb:bb:bb:bb:bb:bb"),
        PCPP_ETHERTYPE_IP
    );

    auto ip  = new pcpp::IPv4Layer(
        pcpp::IPv4Address("10.0.0.1"),
        pcpp::IPv4Address("8.8.8.8")
    );

    auto udp = new pcpp::UdpLayer(12345, dstPort);

    packet.addLayer(eth);
    packet.addLayer(ip);
    packet.addLayer(udp);
    packet.computeCalculateFields();

    return packet;
}

inline pcpp::Packet createUdp6Packet(uint16_t dstPort)
{
    pcpp::Packet packet(100);

   auto* eth = new pcpp::EthLayer(
        pcpp::MacAddress("aa:bb:cc:dd:ee:ff"),
        pcpp::MacAddress("11:22:33:44:55:66"),
        PCPP_ETHERTYPE_IPV6
    );

    auto* ip6 = new pcpp::IPv6Layer(
        pcpp::IPv6Address("2001:db8::10"),
        pcpp::IPv6Address("2001:db8::20")
    );

    auto udp = new pcpp::UdpLayer(12345, dstPort);

    packet.addLayer(eth);
    packet.addLayer(ip6);
    packet.addLayer(udp);
    packet.computeCalculateFields();

    return packet;
}

inline pcpp::Packet createIcmp4Packet()
{
    pcpp::Packet packet(100);

   auto* eth = new pcpp::EthLayer(
        pcpp::MacAddress("aa:bb:cc:dd:ee:ff"),
        pcpp::MacAddress("11:22:33:44:55:66"),
        PCPP_ETHERTYPE_IP
    );

     auto ip  = new pcpp::IPv4Layer(
        pcpp::IPv4Address("8.8.8.8"),
        pcpp::IPv4Address("8.8.4.4")
    );

    auto icmp = new pcpp::IcmpLayer();
    icmp->setEchoRequestData(1, 1, 0, nullptr, 0);

    packet.addLayer(eth);
    packet.addLayer(ip);
    packet.addLayer(icmp);
    packet.computeCalculateFields();

    return packet;
}
