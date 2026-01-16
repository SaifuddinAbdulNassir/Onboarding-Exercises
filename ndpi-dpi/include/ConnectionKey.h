#pragma once

// Standard includes
#include <cstdint>

class ConnectionKey 
{
  public:
    uint32_t dstIp;
    uint16_t dstPort;
    uint8_t  l4Proto;
    uint32_t srcIp;
    uint16_t srcPort;

    bool operator==(const ConnectionKey& o) const;
};
