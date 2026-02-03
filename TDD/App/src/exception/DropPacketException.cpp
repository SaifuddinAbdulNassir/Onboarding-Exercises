#include "exception/DropPacketException.h"

using namespace std;
using namespace TDD;

DropPacketException::DropPacketException(const string &message)
    : runtime_error(message)
{
}
