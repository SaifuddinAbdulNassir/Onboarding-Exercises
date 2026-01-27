#pragma once

// Standard includes
#include <cstddef>

// Project includes
#include "ConnectionKey.h"

namespace ndpi
{

  class ConnectionKeyHash 
  {
    public:
      // Hash function
      size_t operator()(const ConnectionKey& k) const;
  };

}
