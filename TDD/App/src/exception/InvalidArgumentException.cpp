#include "exception/InvalidArgumentException.h"

using namespace std;
using namespace TDD;

// Constructors & destructors

InvalidArgumentException::InvalidArgumentException(const string &message)
    : runtime_error(message)
{
}

InvalidArgumentException::~InvalidArgumentException()
{
}
