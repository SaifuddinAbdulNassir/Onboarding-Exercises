#pragma once

// Standard includes
#include <stdexcept>

namespace TDD
{

  class DropPacketException : public std::runtime_error
  {
  public:
    // Constructors & destructors
    DropPacketException(const std::string &message = "Drop packet");
    virtual ~DropPacketException();
  };

} // namespace TDD
