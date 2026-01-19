#pragma once

// Standard includes
#include <stdexcept>

class DropPacketException : public std::runtime_error 
{
  public:
    DropPacketException();
};
