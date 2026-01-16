#pragma once

// Satndard includes
#include <unordered_map>

// ndpi-dpi includes
#include "ConnectionInfo.h" 
#include "ConnectionKey.h"
#include "ConnectionKeyHash.h"

using namespace std;

typedef unordered_map<ConnectionKey, ConnectionInfo, ConnectionKeyHash> ConnectionsMap;