#include "exception/DropPacketException.h"

using namespace std;

DropPacketException::DropPacketException()
    : runtime_error("Drop packet")
{
}