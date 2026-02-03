#pragma once

// Standard includes
#include <stdexcept>

namespace TDD
{

  class InvalidProtocolException : public std::runtime_error
  {
  public:
    InvalidProtocolException(const std::string &message = "Invalid protocol");
  };

} // namespace TDD
