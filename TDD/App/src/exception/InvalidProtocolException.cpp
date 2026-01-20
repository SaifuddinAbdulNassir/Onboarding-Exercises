#include "exception/InvalidProtocolException.h"

using namespace std;

InvalidProtocolException::InvalidProtocolException(const string& message)
    : runtime_error(message)
{
}
