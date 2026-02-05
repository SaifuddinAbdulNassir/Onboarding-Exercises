// Standard includes
#include <iostream>

// Project includes
#include "Config.h"
#include "NetworkStats.h"
#include "pcap-convert.h"

using namespace pcapconvert;
using namespace pcpp;
using namespace std;

int main(int argc, char *argv[])
{
    Config config;
    PcapConvert pcapConverter;

    if (!pcapConverter.parseArgs(argc, argv, config))
    {
        cerr << "Invalid arguments\n";
        return 1;
    }

    PcapFileReaderDevice reader(config.getInputFile());
    if (!reader.open())
    {
        cerr << "Cannot open input file\n";
        return 1;
    }

    PcapFileWriterDevice writer(config.getOutputFile(), reader.getLinkLayerType());
    if (!writer.open())
    {
        cerr << "Cannot open output file\n";
        return 1;
    }

    pcapConverter.processPackets(reader, writer, config);

    return 0;
}
