#pragma once

// Satndard includes
#include <unordered_map>

// Project includes
#include "ndpi/NdpiConnectionInfo.h"
#include "ndpi/NdpiConnectionKey.h"
#include "ndpi/NdpiConnectionKeyHash.h"

namespace ndpi
{

  typedef std::unordered_map<NdpiConnectionKey, NdpiConnectionInfo, NdpiConnectionKeyHash> NdpiConnectionsMap;

} // namespace ndpi
