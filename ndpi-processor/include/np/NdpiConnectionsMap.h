#pragma once

// Satndard includes
#include <unordered_map>

// Project includes
#include "np/NdpiConnectionInfo.h"
#include "np/NdpiConnectionKey.h"
#include "np/NdpiConnectionKeyHash.h"

namespace np
{

  typedef std::unordered_map<NdpiConnectionKey, NdpiConnectionInfo, NdpiConnectionKeyHash> NdpiConnectionsMap;

} // namespace np
