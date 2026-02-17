#pragma once

// Library includes
#include <ndpi/ndpi_api.h>
#include <sys/signalfd.h>

// Project includes
#include "ndpi/NdpiState.h"

namespace ndpi
{

    class NdpiSignalHandler
    {
    private:
        // Data
        ndpi_global_context *ctx;
        sigset_t mask;
        ndpi_detection_module_struct *ndpiMod;
        int sigFd;

    public:
        // Constructors & destructors
        NdpiSignalHandler();
        virtual ~NdpiSignalHandler();

        // Business logic
        ndpi_detection_module_struct *handleSignal();
        void waitForSignal(NdpiState &ndpiState);
    };

} // namespace ndpi
