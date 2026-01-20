#pragma once

// Standard includes
#include <stdexcept>

class InvalidArgumentException : public std::runtime_error 
{
  public:
    InvalidArgumentException(const std::string& message = "Invalid argument");
};
