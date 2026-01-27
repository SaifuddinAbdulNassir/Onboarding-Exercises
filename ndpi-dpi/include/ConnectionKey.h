#pragma once

// Standard includes
#include <cstdint>

namespace ndpi
{

  class ConnectionKey 
  {
    public:
      // Constructors & destructors 
      ConnectionKey(
          uint32_t dstIp,
          uint16_t dstPort,
          uint8_t  l4Proto,
          uint32_t srcIp,
          uint16_t srcPort);
      ~ConnectionKey();

      // Getters & setters
      uint32_t getDstIp() const { return dstIp; }
      uint16_t getDstPort() const { return dstPort; }
      uint8_t  getL4Proto() const { return l4Proto; }
      uint32_t getSrcIp() const { return srcIp; }
      uint16_t getSrcPort() const { return srcPort; }
      void setDstIp(uint32_t val) { dstIp = val; }
      void setDstPort(uint16_t val) { dstPort = val; }
      void setL4Proto(uint8_t val) { l4Proto = val; }
      void setSrcIp(uint32_t val) { srcIp = val; }
      void setSrcPort(uint16_t val) { srcPort = val; }
  
      // Relational operators
      bool operator==(const ConnectionKey& other) const;

    private:
    // Data
      uint32_t dstIp;
      uint16_t dstPort;
      uint8_t  l4Proto;
      uint32_t srcIp;
      uint16_t srcPort;
  };

} // namespace ndpi
