#include "exception/DuplicatedTargetException.h"

DuplicatedTargetException::DuplicatedTargetException(const string& message)
    : runtime_error(message)
{
}
