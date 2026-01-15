#pragma once

#include <stdexcept>

class DuplicatedTargetException : public std::runtime_error 
{
  public:
    DuplicatedTargetException();
};