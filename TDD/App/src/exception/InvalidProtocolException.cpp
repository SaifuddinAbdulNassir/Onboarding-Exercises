#include "exception/InvalidProtocolException.h"

using namespace std;
using namespace TDD;

InvalidProtocolException::InvalidProtocolException(const string& message)
    : runtime_error(message)
{
}
