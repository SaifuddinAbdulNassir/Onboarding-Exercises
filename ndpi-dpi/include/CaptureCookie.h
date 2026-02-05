#pragma once

// Standard includes
#include <tuple>

// Project includes
#include "AppState.h"
#include "ConnectionsMap.h"

namespace ndpi
{

    typedef std::tuple<ndpi_detection_module_struct *, AppState *, ConnectionsMap *> CaptureCookie;

} // namespace ndpi
