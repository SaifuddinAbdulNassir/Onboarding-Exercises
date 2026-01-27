#pragma once

// Standard includes
#include <string>

using namespace std;

namespace pcapconvert
{

  class Config
  {
    public:
      // Constructor and Destructor
      Config();
      ~Config();
  
      // Getters and Setters
      string getDnsAddr() const {return dnsAddr;}
      int getDnsPort() const {return dnsPort;}
      string getInputFile() const {return inputFile;}
      int getIpVersion() const {return ipVersion;}
      string getOutputFile() const {return outputFile;}
      int getTtlDec() const {return ttlDec;}
      int getVlan() const {return vlan;}
      void setDnsAddr(const string& addr) {dnsAddr = addr;}
      void setDnsPort(int port) {dnsPort = port;}
      void setInputFile(const string& file) {inputFile = file;}
      void setIpVersion(int version) {ipVersion = version;}
      void setOutputFile(const string& file) {outputFile = file;}
      void setTtlDec(int dec) {ttlDec = dec;}
      void setVlan(int id) {vlan = id;}
  
    private:
    // Data
      string dnsAddr;
      int dnsPort = -1;
      string inputFile;
      int ipVersion = -1;
      string outputFile;
      int ttlDec = -1;
      int vlan = -1;
  };

} // namespace pcapconvert
