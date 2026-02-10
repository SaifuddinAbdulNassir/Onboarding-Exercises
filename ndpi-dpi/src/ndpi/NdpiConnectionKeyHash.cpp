#include "ndpi/NdpiConnectionKeyHash.h"

// Standard includes
#include <functional>

using namespace ndpi;
using namespace std;

// Hash function

size_t NdpiConnectionKeyHash::operator()(const NdpiConnectionKey &key) const
{
    return hash<uint64_t>()(((uint64_t)key.getSrcIp() << 32) | key.getDstIp()) ^
           (key.getSrcPort() << 16 | key.getDstPort());
}
