#pragma once

// Standard includes
#include <stdexcept>

namespace TDD
{

  class InvalidProtocolException : public std::runtime_error
  {
  public:
    // Constructors & destructors
    InvalidProtocolException(const std::string &message = "Invalid protocol");
    virtual ~InvalidProtocolException();
  };

} // namespace TDD
