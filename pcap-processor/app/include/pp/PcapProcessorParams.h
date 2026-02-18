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
    std::shared_ptr<const uint16_t> getDnsPort() const { return dnsPort; }
    const std::string &getInputFile() const { return inputFile; }
    std::shared_ptr<const pcpp::IPAddress::AddressType> getIpVersion() const { return ipVersion; }
    const std::string &getOutputFile() const { return outputFile; }
    std::shared_ptr<const uint8_t> getTtlDec() const { return ttlDec; }
    std::shared_ptr<const uint16_t> getVlan() const { return vlan; }
    // Business logic
    bool parseArgs(int argc, char *argv[]);
  };

} // namespace pp
