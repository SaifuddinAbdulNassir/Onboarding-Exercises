#pragma once

// Satndard includes
#include <unordered_map>

// ndpi-dpi includes
#include "ConnectionInfo.h" 
#include "ConnectionKey.h"
#include "ConnectionKeyHash.h"

static std::unordered_map<ConnectionKey, ConnectionInfo, ConnectionKeyHash> gConnectionMap;