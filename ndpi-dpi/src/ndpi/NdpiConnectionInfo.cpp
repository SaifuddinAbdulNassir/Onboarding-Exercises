#include "ndpi/NdpiConnectionInfo.h"

using namespace ndpi;

// Constructors & destructors

NdpiConnectionInfo::NdpiConnectionInfo()
{
}

NdpiConnectionInfo::~NdpiConnectionInfo()
{
	if (flow)
		delete flow;
}
