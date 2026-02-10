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
    void setDstIp(uint32_t val) { dstIp = val; }
    uint16_t getDstPort() const { return dstPort; }
    void setDstPort(uint16_t val) { dstPort = val; }
    uint8_t getL4Proto() const { return l4Proto; }
    void setL4Proto(uint8_t val) { l4Proto = val; }
    uint32_t getSrcIp() const { return srcIp; }
    void setSrcIp(uint32_t val) { srcIp = val; }
    uint16_t getSrcPort() const { return srcPort; }
    void setSrcPort(uint16_t val) { srcPort = val; }

    // Relational operators
    bool operator==(const NdpiConnectionKey &other) const;
  };

} // namespace ndpi
