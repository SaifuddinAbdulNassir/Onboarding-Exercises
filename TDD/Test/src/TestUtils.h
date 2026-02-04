#pragma once

// Library includes
#include <pcapplusplus/EthLayer.h>
#include <pcapplusplus/IcmpLayer.h>
#include <pcapplusplus/IPv4Layer.h>
#include <pcapplusplus/IPv6Layer.h>
#include <pcapplusplus/Packet.h>
#include <pcapplusplus/TcpLayer.h>
#include <pcapplusplus/UdpLayer.h>

using namespace pcpp;

// Constants
const IPv4Address TEST_ADDRESS_1("8.8.8.8");
const IPv4Address TEST_ADDRESS_2("10.0.0.1");
const uint16_t TEST_PORT_1 = 53;
const uint16_t TEST_PORT_2 = 88;
const uint16_t TEST_PORT_3 = 80;
const uint16_t TEST_PORT_4 = 8080;
const uint16_t TEST_PORT_5 = 50;

inline Packet createTcpPacket(uint16_t dstPort)
{
    Packet packet(100);

    auto eth = new EthLayer(
        MacAddress("aa:aa:aa:aa:aa:aa"),
        MacAddress("bb:bb:bb:bb:bb:bb"),
        PCPP_ETHERTYPE_IP);
    auto ip = new IPv4Layer(
        IPv4Address("10.0.0.1"),
        IPv4Address("8.8.8.8"));
    auto tcp = new TcpLayer(12345, dstPort);

    packet.addLayer(eth);
    packet.addLayer(ip);
    packet.addLayer(tcp);
    packet.computeCalculateFields();

    return packet;
}

inline Packet createTcp6Packet(uint16_t dstPort)
{
    Packet packet(100);

    auto *eth = new EthLayer(
        MacAddress("aa:bb:cc:dd:ee:ff"),
        MacAddress("11:22:33:44:55:66"),
        PCPP_ETHERTYPE_IPV6);

    auto *ip6 = new IPv6Layer(
        IPv6Address("2001:db8::1"),
        IPv6Address("2001:db8::2"));

    auto *tcp = new TcpLayer(12345, dstPort);

    packet.addLayer(eth);
    packet.addLayer(ip6);
    packet.addLayer(tcp);
    packet.computeCalculateFields();

    return packet;
}

inline Packet createUdpPacket(uint16_t dstPort)
{
    Packet packet(100);

    auto eth = new EthLayer(
        MacAddress("aa:aa:aa:aa:aa:aa"),
        MacAddress("bb:bb:bb:bb:bb:bb"),
        PCPP_ETHERTYPE_IP);

    auto ip = new IPv4Layer(
        IPv4Address("10.0.0.1"),
        IPv4Address("8.8.8.8"));

    auto udp = new UdpLayer(12345, dstPort);

    packet.addLayer(eth);
    packet.addLayer(ip);
    packet.addLayer(udp);
    packet.computeCalculateFields();

    return packet;
}

inline Packet createUdp6Packet(uint16_t dstPort)
{
    Packet packet(100);

    auto *eth = new EthLayer(
        MacAddress("aa:bb:cc:dd:ee:ff"),
        MacAddress("11:22:33:44:55:66"),
        PCPP_ETHERTYPE_IPV6);

    auto *ip6 = new IPv6Layer(
        IPv6Address("2001:db8::10"),
        IPv6Address("2001:db8::20"));

    auto udp = new UdpLayer(12345, dstPort);

    packet.addLayer(eth);
    packet.addLayer(ip6);
    packet.addLayer(udp);
    packet.computeCalculateFields();

    return packet;
}

inline Packet createIcmp4Packet()
{
    Packet packet(100);

    auto *eth = new EthLayer(
        MacAddress("aa:bb:cc:dd:ee:ff"),
        MacAddress("11:22:33:44:55:66"),
        PCPP_ETHERTYPE_IP);

    auto ip = new IPv4Layer(
        IPv4Address("8.8.8.8"),
        IPv4Address("8.8.4.4"));

    auto icmp = new IcmpLayer();
    icmp->setEchoRequestData(1, 1, 0, nullptr, 0);

    packet.addLayer(eth);
    packet.addLayer(ip);
    packet.addLayer(icmp);
    packet.computeCalculateFields();

    return packet;
}
