#pragma once

// Standard includes
#include <string>

namespace pcapconvert
{

  class Config
  {
  private:
    // Data
    std::string dnsAddr;
    int dnsPort = -1;
    std::string inputFile;
    int ipVersion = -1;
    std::string outputFile;
    int ttlDec = -1;
    int vlan = -1;

  public:
    // Constructor and Destructor
    Config();
    ~Config();

    // Getters and Setters
    std::string getDnsAddr() const { return dnsAddr; }
    int getDnsPort() const { return dnsPort; }
    std::string getInputFile() const { return inputFile; }
    int getIpVersion() const { return ipVersion; }
    std::string getOutputFile() const { return outputFile; }
    int getTtlDec() const { return ttlDec; }
    int getVlan() const { return vlan; }
    void setDnsAddr(const std::string &addr) { dnsAddr = addr; }
    void setDnsPort(int port) { dnsPort = port; }
    void setInputFile(const std::string &file) { inputFile = file; }
    void setIpVersion(int version) { ipVersion = version; }
    void setOutputFile(const std::string &file) { outputFile = file; }
    void setTtlDec(int dec) { ttlDec = dec; }
    void setVlan(int id) { vlan = id; }
  };

} // namespace pcapconvert
