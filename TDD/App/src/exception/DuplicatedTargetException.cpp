#include "exception/DuplicatedTargetException.h"

using namespace std;
using namespace TDD;

// Constructors & destructors

DuplicatedTargetException::DuplicatedTargetException(const string &message)
    : runtime_error(message)
{
}

DuplicatedTargetException::~DuplicatedTargetException()
{
}
