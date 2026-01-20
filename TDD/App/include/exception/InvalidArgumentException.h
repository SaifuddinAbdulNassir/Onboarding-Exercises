#pragma once

// Standard includes
#include <stdexcept>

using namespace std;

class InvalidArgumentException : public runtime_error 
{
  public:
    InvalidArgumentException(const string& message = "Invalid argument");
};