#include "exception/DuplicatedTargetException.h"

DuplicatedTargetException::DuplicatedTargetException()
    : std::runtime_error("Duplicated packet")
{
}