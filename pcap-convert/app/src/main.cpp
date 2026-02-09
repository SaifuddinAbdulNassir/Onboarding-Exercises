// Project includes
#include "pcapconvert/PcapConvert.h"
#include "pcapconvert/PcapConvertParams.h"
#include "pcapconvert/PcapConvertStats.h"

using namespace pcapconvert;
using namespace pcpp;
using namespace std;

int main(int argc, char *argv[])
{
    PcapConvert pcapConverter;

    // Parse command line arguments
    if (!pcapConverter.parseArgs(argc, argv))
    {
        return 1;
    }

    // Process packets
    pcapConverter.processPackets();

    return 0;
}
