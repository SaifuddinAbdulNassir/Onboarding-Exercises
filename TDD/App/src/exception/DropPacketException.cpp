#include "exception/DropPacketException.h"

using namespace std;
using namespace TDD;

// Constructors & destructors

DropPacketException::DropPacketException(const string &message)
    : runtime_error(message)
{
}

DropPacketException::~DropPacketException()
{
}
