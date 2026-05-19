#include "pp/PcapProcessorParams.h"

// Standard includes
#include <iostream>

// Library includes
#include <cxxopts/cxxopts.hpp>

using namespace cxxopts;
using namespace pp;
using namespace pcpp;
using namespace std;

// Constructors & destructors

PcapProcessorParams::PcapProcessorParams()
{
}

PcapProcessorParams::~PcapProcessorParams()
{
}

// Business logic

PcapProcessorParams PcapProcessorParams::create(int argc, char *argv[])
{
    // Define command line options
    Options options("pcap-convert", "PCAP file converter");

    options.add_options()("v,vlan", "VLAN ID to filter on", value<uint16_t>())("ip-version", "IP version to filter on (4 or 6)", value<int>())("t,ttl", "TTL decrement value", value<uint8_t>())("dns-addr", "DNS destination address to modify to", value<string>())("dns-port", "DNS destination port to modify to", value<uint16_t>())("i,input", "Input pcap file path", value<string>())("o,output", "Output pcap file path", value<string>())("h,help", "Command to run the App: ./build/pcap-convert --vlan <vlan id> --ip-version <4|6> --ttl <decrement> --dns-addr <address> --dns-port <port> -i data/captures/<input pcap file> -o data/captures/<output pcap file>");

    // Parse options
    auto result = options.parse(argc, argv);
    if (result.count("help"))
    {
        cout << options.help() << endl;
        exit(0);
    }
    if (!result.count("input") || !result.count("output"))
    {
        throw invalid_argument("Input and output file paths are required.\n" + options.help());
    }

    PcapProcessorParams params;

    // Set parameters based on parsed options
    if (result.count("vlan"))
        params.setVlan(make_shared<uint16_t>(result["vlan"].as<uint16_t>()));
    if (result.count("ip-version"))
    {
        int version = result["ip-version"].as<int>();
        if (version == 4)
            params.setIpVersion(make_shared<IPAddress::AddressType>(IPAddress::IPv4AddressType));
        else if (version == 6)
            params.setIpVersion(make_shared<IPAddress::AddressType>(IPAddress::IPv6AddressType));
        else
        {
            throw invalid_argument("Invalid IP version. Use 4 or 6.\n" + options.help());
        }
    }
    if (result.count("ttl"))
        params.setTtlDec(make_shared<uint8_t>(result["ttl"].as<uint8_t>()));
    if (result.count("dns-addr"))
    {
        params.setDnsAddress(make_shared<IPAddress>(result["dns-addr"].as<string>()));
    }
    if (result.count("dns-port"))
        params.setDnsPort(make_shared<uint16_t>(result["dns-port"].as<uint16_t>()));
    if (result.count("input"))
        params.setInputFile(result["input"].as<string>());
    if (result.count("output"))
        params.setOutputFile(result["output"].as<string>());

    return params;
}
