#include "exception/InvalidArgumentException.h"

InvalidArgumentException::InvalidArgumentException()
    : std::runtime_error("Invalid Argument")
{
}