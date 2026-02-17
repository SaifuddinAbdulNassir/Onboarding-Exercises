// Project includes
#include "pc/PcapProcessor.h"

// Standard includes
#include <iostream>

using namespace pc;
using namespace std;

int main(int argc, char *argv[])
{
    try
    {
        PcapProcessor pcapProcessor(argc, argv);

        // Process packets
        pcapProcessor.processPackets();
    }
    catch (const exception &e)
    {
        cerr << e.what() << '\n';
    }

    return 0;
}
