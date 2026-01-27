#include "ConnectionKeyHash.h"

// Standard includes
#include <functional>

using namespace std;
using namespace ndpi;

// Hash function

size_t ConnectionKeyHash::operator()(const ConnectionKey& k) const 
{
    return hash<uint64_t>()(
        ((uint64_t)k.getSrcIp() << 32) | k.getDstIp()
    ) ^ (k.getSrcPort() << 16 | k.getDstPort());
}
