// Project includes
#include "pp/PcapProcessor.h"

// Standard includes
#include <iostream>

using namespace pp;
using namespace std;

int main(int argc, char *argv[])
{
    try
    {

        auto pcapProcessor = PcapProcessor::create(argc, argv);

        // Process packets
        pcapProcessor.processPackets();
    }
    catch (const exception &e)
    {
        cerr << e.what() << '\n';
    }

    return 0;
}
