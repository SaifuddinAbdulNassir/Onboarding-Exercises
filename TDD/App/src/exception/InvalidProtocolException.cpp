#include "exception/InvalidProtocolException.h"

InvalidProtocolException::InvalidProtocolException(const string& message)
    : runtime_error(message)
{
}