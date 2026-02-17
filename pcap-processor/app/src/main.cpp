// Project includes
#include "pc/PcapProcessor.h"

using namespace pc;

int main(int argc, char *argv[])
{
    PcapProcessor pcapProcessor;

    // Parse command line arguments
    if (!pcapProcessor.parseArgs(argc, argv))
    {
        return 1;
    }

    // Process packets
    pcapProcessor.processPackets();

    return 0;
}
