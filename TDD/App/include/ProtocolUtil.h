#pragma once

// Library includes
#include <pcapplusplus/Packet.h>

// Project includes
#include "enums/ProtocolTypes.h"

class ProtocolUtil 
{
  public:
    // Protocol detector
    static Protocol detect(pcpp::Packet& packet);
};
