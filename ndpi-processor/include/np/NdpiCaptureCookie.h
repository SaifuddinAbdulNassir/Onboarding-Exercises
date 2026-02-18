#pragma once

// Standard includes
#include <tuple>

// Project includes
#include "np/NdpiConnectionsMap.h"
#include "np/NdpiState.h"

namespace np
{

    typedef std::tuple<ndpi_detection_module_struct *, NdpiState *, NdpiConnectionsMap *> NdpiCaptureCookie;

} // namespace np
