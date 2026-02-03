#include "ConnectionInfo.h"

using namespace ndpi;

// Constants

const bool ConnectionInfo::DEFAULT_BOOL = false;
const size_t ConnectionInfo::DEFAULT_SIZE_T = 0;
const std::string ConnectionInfo::DEFAULT_STRING = "";
const std::nullptr_t ConnectionInfo::NULLPTR = nullptr;

// Constructors & destructors

ConnectionInfo::ConnectionInfo()
	: category(DEFAULT_STRING), domain(DEFAULT_STRING), done(DEFAULT_BOOL), flow(NULLPTR), packetCount(DEFAULT_SIZE_T), protocol(DEFAULT_STRING), uid(DEFAULT_SIZE_T)
{
}

ConnectionInfo::~ConnectionInfo()
{
	if(flow)
		delete flow;
}
