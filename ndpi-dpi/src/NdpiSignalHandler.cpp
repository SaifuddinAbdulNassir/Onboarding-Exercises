#include "NdpiSignalHandler.h"

// Standard includes
#include <csignal>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <poll.h>
#include <unistd.h>

using namespace ndpi;
using namespace std;

// Constructors & destructors

NdpiSignalHandler::NdpiSignalHandler()
{
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
}

NdpiSignalHandler::~NdpiSignalHandler()
{
    close(sigFd);
    ndpi_global_deinit(ctx);
    ndpi_exit_detection_module(ndpiMod);
}

// Business logic

ndpi_detection_module_struct *NdpiSignalHandler::handleSignal()
{
    // Block SIGINT signal and create signalfd to receive it
    if (sigprocmask(SIG_BLOCK, &mask, nullptr) == -1)
    {
        cerr << "sigprocmask";
        return nullptr;
    }

    // Create signalfd to receive SIGINT signals
    sigFd = signalfd(-1, &mask, SFD_CLOEXEC);
    if (sigFd == -1)
    {
        cerr << "signalfd";
        return nullptr;
    }

    // Initialize nDPI
    ctx = ndpi_global_init();
    ndpiMod = ndpi_init_detection_module(ctx);

    if (!ndpiMod)
    {
        cerr << "nDPI init failed\n";
        return nullptr;
    }

    // Enable all protocols for detection
    NDPI_PROTOCOL_BITMASK all;
    NDPI_BITMASK_SET_ALL(all);

    // Configure nDPI to detect all protocols and finalize initialization
    ndpi_set_protocol_detection_bitmask2(ndpiMod, &all);
    ndpi_finalize_initialization(ndpiMod);

    return ndpiMod;
}

void NdpiSignalHandler::waitForSignal(NdpiState &ndpiState)
{
    // Wait for SIGINT signal to gracefully shutdown the application
    while (ndpiState.getRunning())
    {
        // Use poll to wait for a signal on the signalfd
        pollfd pfd;
        pfd.fd = sigFd;
        pfd.events = POLLIN;
        pfd.revents = 0;

        // If a signal is received, read it and check if it's SIGINT to set running to false
        int rc = poll(&pfd, 1, 1000);
        if (rc > 0 && (pfd.revents & POLLIN))
        {
            signalfd_siginfo si;
            ssize_t n = read(sigFd, &si, sizeof(si));
            if (n == (ssize_t)sizeof(si) && si.ssi_signo == SIGINT)
                ndpiState.setRunning(false);
        }
    }
}
