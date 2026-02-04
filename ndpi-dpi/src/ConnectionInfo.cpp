#include "ConnectionInfo.h"

using namespace ndpi;

// Constructors & destructors

ConnectionInfo::ConnectionInfo()
	: category(DEFAULT_STRING), domain(DEFAULT_STRING), done(DEFAULT_BOOL), flow(NULLPTR), packetCount(DEFAULT_SIZE_T), protocol(DEFAULT_STRING), uid(DEFAULT_SIZE_T)
{
}

ConnectionInfo::~ConnectionInfo()
{
	if (flow)
		delete flow;
}
