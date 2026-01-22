#pragma once

// Library includes
#include <third-party/better-enums/enum.h>

BETTER_ENUM(Protocol, int,
    TCP4,
    TCP6,
    UDP4,
    UDP6,
    UNKNOWN
);
