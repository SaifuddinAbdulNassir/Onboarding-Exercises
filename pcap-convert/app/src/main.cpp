// Standard includes
#include <iostream>

// Project includes
#include "pcap-convert.h"
#include "PcapConvertParams.h"
#include "PcapConvertStats.h"

using namespace pcapconvert;
using namespace pcpp;
using namespace std;

int main(int argc, char *argv[])
{
    PcapConvertParams params;
    PcapConvert pcapConverter;

    if (!pcapConverter.parseArgs(argc, argv, params))
    {
        cerr << "Invalid arguments\n";
        return 1;
    }

    PcapFileReaderDevice reader(params.getInputFile());
    if (!reader.open())
    {
        cerr << "Cannot open input file\n";
        return 1;
    }

    PcapFileWriterDevice writer(params.getOutputFile(), reader.getLinkLayerType());
    if (!writer.open())
    {
        cerr << "Cannot open output file\n";
        return 1;
    }

    pcapConverter.processPackets(reader, writer, params);

    return 0;
}
