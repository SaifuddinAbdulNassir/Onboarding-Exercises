#pragma once 

// Standard includes
#include <cstdint>
#include <string>

// Library includes
extern "C" {
#include "/usr/include/ndpi/ndpi_api.h"
}

class ConnectionInfo 
{
  public:
    bool done;
    ndpi_flow_struct* flow;
    std::string category;
    std::string domain;
    std::string protocol;
    uint32_t packetCount;
    uint64_t uid;
};