#pragma once

// Satndard includes
#include <unordered_map>

// Project includes
#include "ConnectionInfo.h" 
#include "ConnectionKey.h"
#include "ConnectionKeyHash.h"

namespace ndpi
{

  typedef std::unordered_map<ConnectionKey, ConnectionInfo, ConnectionKeyHash> ConnectionsMap;

} // namespace ndpi
