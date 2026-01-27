#include "ConnectionKey.h"

// Relational operators

bool ConnectionKey::operator==(const ConnectionKey& o) const 
{
    return srcIp == o.srcIp &&
           dstIp == o.dstIp &&
           srcPort == o.srcPort &&
           dstPort == o.dstPort &&
           l4Proto == o.l4Proto;
}