#pragma once

// Standard includes
#include <cstddef>

// Project includes
#include "np/NdpiConnectionKey.h"

namespace np
{

  class NdpiConnectionKeyHash
  {
  public:
    // Hash function
    size_t operator()(const NdpiConnectionKey &key) const;
  };

} // namespace np
