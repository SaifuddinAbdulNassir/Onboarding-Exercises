#pragma once

// Standard includes
#include <string>

using namespace std;

class Config
{
  public:
    string getDnsAddr() const;
    int getDnsPort() const;
    string getInputFile() const;
    int getIpVersion() const;
    string getOutputFile() const;
    int getTtlDec() const;
    int getVlan() const;

    void setDnsAddr(const string& addr);
    void setDnsPort(int port);
    void setInputFile(const string& file);
    void setIpVersion(int version);
    void setOutputFile(const string& file);
    void setTtlDec(int dec);
    void setVlan(int id);

  private:
    string dnsAddr;
    int dnsPort = -1;
    string inputFile;
    int ipVersion = -1;
    string outputFile;
    int ttlDec = -1;
    int vlan = -1;
};
