#pragma once

// Standard includes
#include <cstdint>

namespace ndpi
{

  class NdpiConnectionKey
  {
  private:
    // Data
    uint32_t dstIp;
    uint16_t dstPort;
    uint8_t l4Proto;
    uint32_t srcIp;
    uint16_t srcPort;

  public:
    // Constructors & destructors
    NdpiConnectionKey(uint32_t dstIp, uint16_t dstPort, uint8_t l4Proto, uint32_t srcIp, uint16_t srcPort);
    virtual ~NdpiConnectionKey();

    // Getters & setters
    uint32_t getDstIp() const { return dstIp; }
    uint16_t getDstPort() const { return dstPort; }
    uint32_t getSrcIp() const { return srcIp; }
    uint16_t getSrcPort() const { return srcPort; }

    // Relational operators
    bool operator==(const NdpiConnectionKey &other) const;
  };

} // namespace ndpi
