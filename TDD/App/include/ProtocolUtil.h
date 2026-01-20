#pragma once

// Library includes
#include <pcapplusplus/Packet.h>

// Project includes
#include "enums/ProtocolTypes.h"

using namespace pcpp;

class ProtocolUtil 
{
  public:
    // Protocol detector
    static Protocol detect(Packet& packet);
};
