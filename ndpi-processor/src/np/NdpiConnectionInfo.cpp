#include "np/NdpiConnectionInfo.h"

using namespace np;

// Constructors & destructors

NdpiConnectionInfo::NdpiConnectionInfo()
{
}

NdpiConnectionInfo::~NdpiConnectionInfo()
{
	if (flow)
		delete flow;
}
