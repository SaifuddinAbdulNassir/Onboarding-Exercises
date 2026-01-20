#include "exception/DropPacketException.h"

DropPacketException::DropPacketException(const string& message)
    : runtime_error(message)
{
}
