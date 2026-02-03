#pragma once

// Standard includes
#include <stdexcept>

namespace TDD
{

  class InvalidArgumentException : public std::runtime_error
  {
  public:
    InvalidArgumentException(const std::string &message = "Invalid argument");
  };

} // namespace TDD
