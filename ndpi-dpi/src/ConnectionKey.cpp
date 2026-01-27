#include "ConnectionKey.h"

using namespace ndpi;

// Relational operators

bool ConnectionKey::operator==(const ConnectionKey& o) const 
{
    return srcIp == o.srcIp &&
           dstIp == o.dstIp &&
           srcPort == o.srcPort &&
           dstPort == o.dstPort &&
           l4Proto == o.l4Proto;
}
