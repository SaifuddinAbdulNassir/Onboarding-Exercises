#pragma once

// Standard includes
#include <stdexcept>

using namespace std;

class DuplicatedTargetException : public runtime_error 
{
  public:
    DuplicatedTargetException(const string& message = "Duplicated target");
};