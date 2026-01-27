#pragma once

// Standard includes
#include <cstdint>

namespace ndpi
{

  class ConnectionKey 
  {
    public:
    // Data
      uint32_t dstIp;
      uint16_t dstPort;
      uint8_t  l4Proto;
      uint32_t srcIp;
      uint16_t srcPort;
  
      // Relational operators
      bool operator==(const ConnectionKey& o) const;
  };

} // namespace ndpi
