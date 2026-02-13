// Project includes
#include "pcapconverter/PcapConverter.h"
#include "pcapconverter/PcapConverterParams.h"
#include "pcapconverter/PcapConverterStats.h"

using namespace pcapconverter;
using namespace pcpp;
using namespace std;

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
