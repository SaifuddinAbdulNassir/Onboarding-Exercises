#pragma once

// Standard includes
#include <tuple>

// Project includes
#include "ConnectionsMap.h"
#include "NdpiState.h"

namespace ndpi
{

    typedef std::tuple<ndpi_detection_module_struct *, NdpiState *, ConnectionsMap *> CaptureCookie;

} // namespace ndpi
