#pragma once

#include <pcapplusplus/Packet.h>

#include "enums/ProtocolEnum.h"

class ProtocolUtil 
{
  public:
    static Protocol detect(pcpp::Packet& packet);
};
