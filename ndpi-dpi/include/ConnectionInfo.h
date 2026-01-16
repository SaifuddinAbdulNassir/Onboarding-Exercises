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
    std::string category;
    std::string domain;
    bool done;
    ndpi_flow_struct* flow;
    uint32_t packetCount;
    std::string protocol;
    uint64_t uid;
};