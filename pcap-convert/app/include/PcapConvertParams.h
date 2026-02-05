#pragma once

// Standard includes
#include <string>
#include <memory>

namespace pcapconvert
{

  class PcapConvertParams
  {
  private:
    // Data
    std::string dnsAddr;
    std::unique_ptr<uint16_t> dnsPort = nullptr;
    std::string inputFile;
    int ipVersion = -1;
    std::string outputFile;
    std::unique_ptr<uint8_t> ttlDec = nullptr;
    std::unique_ptr<uint16_t> vlan = nullptr;

  public:
    // Constructors & destructors
    PcapConvertParams();
    virtual ~PcapConvertParams();

    // Getters & setters
    const std::string &getDnsAddr() const { return dnsAddr; }
    uint16_t *getDnsPort() const { return dnsPort.get(); }
    const std::string &getInputFile() const { return inputFile; }
    int getIpVersion() const { return ipVersion; }
    const std::string &getOutputFile() const { return outputFile; }
    uint8_t *getTtlDec() const { return ttlDec.get(); }
    uint16_t *getVlan() const { return vlan.get(); }
    void setDnsAddr(const std::string &addr) { dnsAddr = addr; }
    void setDnsPort(std::unique_ptr<uint16_t> port) { dnsPort = std::move(port); }
    void setInputFile(const std::string &file) { inputFile = file; }
    void setIpVersion(int version) { ipVersion = version; }
    void setOutputFile(const std::string &file) { outputFile = file; }
    void setTtlDec(std::unique_ptr<uint8_t> dec) { ttlDec = std::move(dec); }
    void setVlan(std::unique_ptr<uint16_t> id) { vlan = std::move(id); }
  };

} // namespace pcapconvert
