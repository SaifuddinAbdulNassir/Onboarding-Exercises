#include "exception/InvalidArgumentException.h"

using namespace std;

InvalidArgumentException::InvalidArgumentException(const string& message)
    : runtime_error(message)
{
}
