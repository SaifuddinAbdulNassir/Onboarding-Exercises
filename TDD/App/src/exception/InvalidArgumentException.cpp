#include "exception/InvalidArgumentException.h"

InvalidArgumentException::InvalidArgumentException(const string& message)
    : runtime_error(message)
{
}
