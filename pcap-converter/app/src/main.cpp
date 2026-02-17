// Project includes
#include "pcapconverter/PcapConverter.h"

using namespace pcapconverter;

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
