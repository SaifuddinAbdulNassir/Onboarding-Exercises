// Project includes
#include "CaptureCookie.h"
#include "NdpiProcessor.h"
#include "NdpiSignalHandler.h"

using namespace ndpi;

int main(int argc, char *argv[])
{

    NdpiProcessor ndpiProcessor;

    // Parse command line arguments
    if (!ndpiProcessor.ParseArgs(argc, argv))
    {
        return 1;
    }

    // Process live packets
    ndpiProcessor.processLivePackets();

    return 0;
}
