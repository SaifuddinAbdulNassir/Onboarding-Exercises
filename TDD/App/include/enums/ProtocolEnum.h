#pragma once

#include <third-party/better-enums/enum.h>   // better-enums

BETTER_ENUM(Protocol, int,
    TCP4,
    TCP6,
    UDP4,
    UDP6,
    UNKNOWN
);
