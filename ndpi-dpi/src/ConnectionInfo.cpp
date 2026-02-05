#include "ConnectionInfo.h"

using namespace ndpi;

// Constructors & destructors

ConnectionInfo::ConnectionInfo()
{
}

ConnectionInfo::~ConnectionInfo()
{
	if (flow)
		delete flow;
}
