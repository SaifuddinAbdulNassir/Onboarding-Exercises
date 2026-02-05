#include "PcapConvertParams.h"

using namespace pcapconvert;
using namespace pcpp;
using namespace std;

// Constructors & destructors

PcapConvertParams::PcapConvertParams()
{
}

PcapConvertParams::~PcapConvertParams()
{
}

void PcapConvertParams::setDnsAddr(const std::string &addr)
{
    if (IPv4Address::isValidIPv4Address(addr))
    {
        dnsAddr = std::make_unique<std::variant<IPv4Address, IPv6Address>>(IPv4Address(addr));
    }
    else
    {
        dnsAddr = std::make_unique<std::variant<IPv4Address, IPv6Address>>(IPv6Address(addr));
    }
}
