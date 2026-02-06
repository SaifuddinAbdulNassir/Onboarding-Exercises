#pragma once

// Standard includes
#include <iostream>
#include <memory>
#include <string>
#include <variant>

// Library includes
#include <pcapplusplus/IpAddress.h>

namespace pcapconvert
{

  class PcapConvertParams
  {
  private:
    // Data
    std::shared_ptr<pcpp::IPv4Address> dnsV4Address = nullptr;
    std::shared_ptr<pcpp::IPv6Address> dnsV6Address = nullptr;
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
    std::shared_ptr<pcpp::IPv4Address> getDnsV4Addr() const { return dnsV4Address; }
    void setDnsV4Addr(const std::shared_ptr<pcpp::IPv4Address> v4Addr) { dnsV4Address = v4Addr; }
    std::shared_ptr<pcpp::IPv6Address> getDnsV6Addr() const { return dnsV6Address; }
    void setDnsV6Addr(const std::shared_ptr<pcpp::IPv6Address> v6Addr) { dnsV6Address = v6Addr; }
    uint16_t *getDnsPort() const { return dnsPort.get(); }
    void setDnsPort(std::unique_ptr<uint16_t> port) { dnsPort = std::move(port); }
    const std::string &getInputFile() const { return inputFile; }
    void setInputFile(const std::string &file) { inputFile = file; }
    const pcpp::IPAddress::AddressType &getIpVersion() const { return ipVersion; }
    void setIpVersion(const pcpp::IPAddress::AddressType &version) { ipVersion = version; }
    const std::string &getOutputFile() const { return outputFile; }
    void setOutputFile(const std::string &file) { outputFile = file; }
    uint8_t *getTtlDec() const { return ttlDec.get(); }
    void setTtlDec(std::unique_ptr<uint8_t> dec) { ttlDec = std::move(dec); }
    uint16_t *getVlan() const { return vlan.get(); }
    void setVlan(std::unique_ptr<uint16_t> id) { vlan = std::move(id); }
  };

} // namespace pcapconvert
