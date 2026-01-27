#include "exception/DuplicatedTargetException.h"

using namespace std;

DuplicatedTargetException::DuplicatedTargetException(const string& message)
    : runtime_error(message)
{
}
