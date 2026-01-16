#pragma once

// Standard includes
#include <cstdint>

class ConnectionKey 
{
  public:
    uint8_t  l4Proto;
    uint16_t dstPort;
    uint16_t srcPort;
    uint32_t dstIp;
    uint32_t srcIp;

    bool operator==(const ConnectionKey& o) const;
};
