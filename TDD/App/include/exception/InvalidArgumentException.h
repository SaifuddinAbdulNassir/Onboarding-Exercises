#pragma once

// Standard includes
#include <stdexcept>

namespace TDD
{

  class InvalidArgumentException : public std::runtime_error
  {
  public:
    // Constructors & destructors
    InvalidArgumentException(const std::string &message = "Invalid argument");
    virtual ~InvalidArgumentException();
  };

} // namespace TDD
