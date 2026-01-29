#include "ConnectionInfo.h"

using namespace ndpi;

// Constructors & destructors

ConnectionInfo::ConnectionInfo()
	: category(""), domain(""), done(false), flow(nullptr), packetCount(0), protocol(""), uid(0)
{
}

ConnectionInfo::~ConnectionInfo()
{
	if(flow)
		delete flow;
}
