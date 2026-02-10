#pragma once

// Standard includes
#include <cstddef>

// Project includes
#include "ndpi/NdpiConnectionKey.h"

namespace ndpi
{

  class NdpiConnectionKeyHash
  {
  public:
    // Hash function
    size_t operator()(const NdpiConnectionKey &key) const;
  };

} // namespace ndpi
