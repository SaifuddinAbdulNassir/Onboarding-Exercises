// Project includes
#include "PcapConvert.h"
#include "PcapConvertParams.h"
#include "PcapConvertStats.h"

using namespace pcapconvert;
using namespace pcpp;
using namespace std;

int main(int argc, char *argv[])
{
    PcapConvert pcapConverter;

    if (!pcapConverter.parseArgs(argc, argv))
    {
        cerr << "Invalid arguments\n";
        return 1;
    }

    pcapConverter.processPackets();

    return 0;
}
