#include "exception/DuplicatedTargetException.h"

using namespace std;

DuplicatedTargetException::DuplicatedTargetException()
    : runtime_error("Duplicated packet")
{
}