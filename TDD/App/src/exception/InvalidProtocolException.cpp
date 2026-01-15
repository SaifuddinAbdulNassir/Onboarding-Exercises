#include "exception/InvalidProtocolException.h"

InvalidProtocolException::InvalidProtocolException()
    : std::runtime_error("Invalid Protocol")
{
}