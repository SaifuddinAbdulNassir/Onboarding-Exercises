#pragma once

// Standard includes
#include <tuple>

// Project includes
#include "ndpi/NdpiConnectionsMap.h"
#include "ndpi/NdpiState.h"

namespace ndpi
{

    typedef std::tuple<ndpi_detection_module_struct *, NdpiState *, NdpiConnectionsMap *> NdpiCaptureCookie;

} // namespace ndpi
