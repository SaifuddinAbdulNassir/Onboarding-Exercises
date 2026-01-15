#include "exception/DropPacketException.h"

DropPacketException::DropPacketException()
    : std::runtime_error("Drop packet")
{
}