// Project includes
#include "np/NdpiProcessor.h"

using namespace np;

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
