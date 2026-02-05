#pragma once

// Standard includes
#include <iostream>
#include <string>
#include <memory>
#include <variant>

// Library includes
#include <pcapplusplus/IpAddress.h>

namespace pcapconvert
{

  class PcapConvertParams
  {
  private:
    // Data
    std::unique_ptr<std::variant<pcpp::IPv4Address, pcpp::IPv6Address>> dnsAddr = nullptr;
    std::unique_ptr<uint16_t> dnsPort = nullptr;
    std::string inputFile;
    pcpp::IPAddress::AddressType ipVersion = pcpp::IPAddress::IPv4AddressType;
    std::string outputFile;
    std::unique_ptr<uint8_t> ttlDec = nullptr;
    std::unique_ptr<uint16_t> vlan = nullptr;

  public:
    // Constructors & destructors
    PcapConvertParams();
    virtual ~PcapConvertParams();

    // Getters & setters
    std::variant<pcpp::IPv4Address, pcpp::IPv6Address> *getDnsAddr() const { return dnsAddr.get(); }
    uint16_t *getDnsPort() const { return dnsPort.get(); }
    const std::string &getInputFile() const { return inputFile; }
    const pcpp::IPAddress::AddressType &getIpVersion() const { return ipVersion; }
    const std::string &getOutputFile() const { return outputFile; }
    uint8_t *getTtlDec() const { return ttlDec.get(); }
    uint16_t *getVlan() const { return vlan.get(); }
    void setDnsAddr(const std::string &addr);
    void setDnsPort(std::unique_ptr<uint16_t> port) { dnsPort = std::move(port); }
    void setInputFile(const std::string &file) { inputFile = file; }
    void setIpVersion(const pcpp::IPAddress::AddressType &version) { ipVersion = version; }
    void setOutputFile(const std::string &file) { outputFile = file; }
    void setTtlDec(std::unique_ptr<uint8_t> dec) { ttlDec = std::move(dec); }
    void setVlan(std::unique_ptr<uint16_t> id) { vlan = std::move(id); }
  };

} // namespace pcapconvert
