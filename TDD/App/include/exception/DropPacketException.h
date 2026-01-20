#pragma once

// Standard includes
#include <stdexcept>

using namespace std;

class DropPacketException : public runtime_error 
{
  public:
    DropPacketException(const string& message = "Drop packet");
};
