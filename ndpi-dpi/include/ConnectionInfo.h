#pragma once 

// Standard includes
#include <cstdint>
#include <string>

// Library includes
extern "C" {
#include <ndpi_api.h>
}

class ConnectionInfo 
{
  public:
    ConnectionInfo();
    ~ConnectionInfo();

    std::string category;
    std::string domain;
    bool done;
    ndpi_flow_struct* flow;
    uint32_t packetCount;
    std::string protocol;
    uint64_t uid;
};