#pragma once 

#include <cstdint>
#include <string>

extern "C" {
#include "/usr/include/ndpi/ndpi_api.h"
}

struct ConnectionInfo {
    uint64_t uid;
    ndpi_flow_struct* flow;
    uint32_t packet_count;
    bool done;

    std::string protocol;
    std::string category;
    std::string domain;
};