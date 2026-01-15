#pragma once

#include <string>

struct Config
{
    std::string inputFile;
    std::string outputFile = "output.pcap";
    int vlan = -1;
    int ipVersion = -1;
    int ttlDec = -1;
    std::string dnsAddr;
    int dnsPort = -1;
};