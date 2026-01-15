#pragma once

#include <stdexcept>

class InvalidProtocolException : public std::runtime_error 
{
  public:
    InvalidProtocolException();
};