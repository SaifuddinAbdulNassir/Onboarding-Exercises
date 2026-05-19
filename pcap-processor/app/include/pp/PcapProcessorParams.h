#pragma once

// Library includes
#include <pcapplusplus/IpAddress.h>

namespace pp
{

  class PcapProcessorParams
  {
  private:
    // Data
    std::shared_ptr<pcpp::IPAddress> dnsAddress;
    std::shared_ptr<uint16_t> dnsPort;
    std::string inputFile;
    std::shared_ptr<pcpp::IPAddress::AddressType> ipVersion;
    std::string outputFile;
    std::shared_ptr<uint8_t> ttlDec;
    std::shared_ptr<uint16_t> vlan;

  public:
    // Constructors & destructors
    PcapProcessorParams();
    virtual ~PcapProcessorParams();

    // Getters & setters
    std::shared_ptr<const pcpp::IPAddress> getDnsAddress() const { return dnsAddress; }
    void setDnsAddress(const std::shared_ptr<pcpp::IPAddress> addr) { dnsAddress = addr; }
    std::shared_ptr<const uint16_t> getDnsPort() const { return dnsPort; }
    void setDnsPort(const std::shared_ptr<uint16_t> port) { dnsPort = port; }
    const std::string &getInputFile() const { return inputFile; }
    void setInputFile(const std::string &file) { inputFile = file; }
    std::shared_ptr<const pcpp::IPAddress::AddressType> getIpVersion() const { return ipVersion; }
    void setIpVersion(const std::shared_ptr<pcpp::IPAddress::AddressType> version) { ipVersion = version; }
    const std::string &getOutputFile() const { return outputFile; }
    void setOutputFile(const std::string &file) { outputFile = file; }
    std::shared_ptr<const uint8_t> getTtlDec() const { return ttlDec; }
    void setTtlDec(const std::shared_ptr<uint8_t> ttl) { ttlDec = ttl; }
    std::shared_ptr<const uint16_t> getVlan() const { return vlan; }
    void setVlan(const std::shared_ptr<uint16_t> v) { vlan = v; }

    // Business logic
    static PcapProcessorParams create(int argc, char *argv[]);
  };

} // namespace pp
