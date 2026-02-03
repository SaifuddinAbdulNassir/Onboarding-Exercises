#pragma once

// Standard includes
#include <stdexcept>

namespace TDD
{

  class DropPacketException : public std::runtime_error 
  {
    public:
      DropPacketException(const std::string &message = "Drop packet");
  };
  
} // namespace TDD
