#pragma once

// Satndard includes
#include <unordered_map>

// Project includes
#include "ConnectionInfo.h" 
#include "ConnectionKey.h"
#include "ConnectionKeyHash.h"

using namespace std;

namespace ndpi
{

  typedef unordered_map<ConnectionKey, ConnectionInfo, ConnectionKeyHash> ConnectionsMap;

} // namespace ndpi
