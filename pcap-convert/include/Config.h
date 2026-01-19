#pragma once

// Standard includes
#include <string>

class Config
{
  public:
    std::string dnsAddr;
    int dnsPort = -1;
    std::string inputFile;
    int ipVersion = -1;
    std::string outputFile;
    int ttlDec = -1;
    int vlan = -1;
};
