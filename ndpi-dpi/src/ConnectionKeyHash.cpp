#include "ConnectionKeyHash.h"

// Standard includes
#include <functional>

using namespace std;
using namespace ndpi;

// Hash function

size_t ConnectionKeyHash::operator()(const ConnectionKey& key) const 
{
    return hash<uint64_t>()(
        ((uint64_t)key.getSrcIp() << 32) | key.getDstIp()
    ) ^ (key.getSrcPort() << 16 | key.getDstPort());
}
