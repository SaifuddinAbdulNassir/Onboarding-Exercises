#include "exception/InvalidProtocolException.h"

using namespace std;

InvalidProtocolException::InvalidProtocolException()
    : runtime_error("Invalid Protocol")
{
}