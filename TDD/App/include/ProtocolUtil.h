#pragma once

// Library includes
#include <pcapplusplus/Packet.h>

// Project includes
#include "enums/ProtocolEnum.h"

class ProtocolUtil 
{
  public:
    static Protocol detect(pcpp::Packet& packet);
};
