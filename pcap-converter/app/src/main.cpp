// Project includes
#include "pc/PcapConverter.h"

using namespace pc;

int main(int argc, char *argv[])
{
    PcapConverter pcapConverter;

    // Parse command line arguments
    if (!pcapConverter.parseArgs(argc, argv))
    {
        return 1;
    }

    // Process packets
    pcapConverter.processPackets();

    return 0;
}
