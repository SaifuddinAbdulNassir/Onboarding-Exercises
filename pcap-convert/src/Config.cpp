#include "Config.h"

std::string Config::getDnsAddr() const
{
    return dnsAddr;
}

int Config::getDnsPort() const
{
    return dnsPort;
}

std::string Config::getInputFile() const
{
    return inputFile;
}

int Config::getIpVersion() const
{
    return ipVersion;
}

std::string Config::getOutputFile() const
{
    return outputFile;
}

int Config::getTtlDec() const
{
    return ttlDec;
}

int Config::getVlan() const
{
    return vlan;
}

void Config::setDnsAddr(const std::string &addr)
{
    dnsAddr = addr;
}

void Config::setDnsPort(int port)
{
    dnsPort = port;
}

void Config::setInputFile(const std::string &file)
{
    inputFile = file;
}

void Config::setIpVersion(int version)
{
    ipVersion = version;
}

void Config::setOutputFile(const std::string &file)
{
    outputFile = file;
}

void Config::setTtlDec(int dec)
{
    ttlDec = dec;
}

void Config::setVlan(int id)
{
    vlan = id;
}