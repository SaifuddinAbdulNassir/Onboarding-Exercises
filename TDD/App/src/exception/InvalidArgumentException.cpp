#include "exception/InvalidArgumentException.h"

using namespace std;
using namespace TDD;

InvalidArgumentException::InvalidArgumentException(const string& message)
    : runtime_error(message)
{
}
