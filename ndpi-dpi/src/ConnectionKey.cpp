#include "ConnectionKey.h"

using namespace ndpi;

// Constructors & destructors

ConnectionKey::ConnectionKey(
          uint32_t dstIp,
          uint16_t dstPort,
          uint8_t  l4Proto,
          uint32_t srcIp,
          uint16_t srcPort) :
          dstIp(dstIp),
          dstPort(dstPort),
          l4Proto(l4Proto),
          srcIp(srcIp),
          srcPort(srcPort)
{
}

ConnectionKey::~ConnectionKey()
{
}

// Relational operators

bool ConnectionKey::operator==(const ConnectionKey& other) const 
{
    return srcIp == other.srcIp &&
           dstIp == other.dstIp &&
           srcPort == other.srcPort &&
           dstPort == other.dstPort &&
           l4Proto == other.l4Proto;
}
