#include "exception/DropPacketException.h"

using namespace std;

DropPacketException::DropPacketException(const string& message)
    : runtime_error(message)
{
}
