#pragma once

// Standard includes
#include <cstddef>

//ndpi-dpi includes
#include "ConnectionKey.h"

class ConnectionKeyHash 
{
  public:
    size_t operator()(const ConnectionKey& k) const;
};
