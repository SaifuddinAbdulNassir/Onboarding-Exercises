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

bool ConnectionKey::operator==(const ConnectionKey& o) const 
{
    return srcIp == o.srcIp &&
           dstIp == o.dstIp &&
           srcPort == o.srcPort &&
           dstPort == o.dstPort &&
           l4Proto == o.l4Proto;
}
