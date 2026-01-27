#include "ConnectionKeyHash.h"

// Standard includes
#include <functional>

using namespace std;

// Hash function

size_t ConnectionKeyHash::operator()(const ConnectionKey& k) const 
{
    return hash<uint64_t>()(
        ((uint64_t)k.srcIp << 32) | k.dstIp
    ) ^ (k.srcPort << 16 | k.dstPort);
}