#pragma once

// Standard includes
#include <stdexcept>

using namespace std;

class InvalidProtocolException : public runtime_error 
{
  public:
    InvalidProtocolException(const string& message = "Invalid protocol");
};