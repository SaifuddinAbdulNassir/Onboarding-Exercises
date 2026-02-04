#include "exception/InvalidProtocolException.h"

using namespace std;
using namespace TDD;

// Constructors & destructors

InvalidProtocolException::InvalidProtocolException(const string &message)
    : runtime_error(message)
{
}

InvalidProtocolException::~InvalidProtocolException()
{
}
