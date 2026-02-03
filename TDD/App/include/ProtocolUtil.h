#pragma once

// Library includes
#include <pcapplusplus/Packet.h>

// Project includes
#include "enums/Protocol.h"

namespace TDD
{

  class ProtocolUtil 
  {
    public:
      // Protocol detector
      static Protocol detect(pcpp::Packet &packet);
  };

} // namespace TDD
