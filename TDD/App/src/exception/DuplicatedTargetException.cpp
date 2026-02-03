#include "exception/DuplicatedTargetException.h"

using namespace std;
using namespace TDD;

DuplicatedTargetException::DuplicatedTargetException(const string &message)
    : runtime_error(message)
{
}
