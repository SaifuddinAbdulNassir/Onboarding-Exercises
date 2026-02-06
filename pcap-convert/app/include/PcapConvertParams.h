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
    std::shared_ptr<pcpp::IPv4Address> dnsV4Address;
    std::shared_ptr<pcpp::IPv6Address> dnsV6Address;
    std::shared_ptr<uint16_t> dnsPort;
    std::string inputFile;
    std::shared_ptr<pcpp::IPAddress::AddressType> ipVersion;
    std::string outputFile;
    std::shared_ptr<uint8_t> ttlDec;
    std::shared_ptr<uint16_t> vlan;

  public:
    // Constructors & destructors
    PcapConvertParams();
    virtual ~PcapConvertParams();

    // Getters & setters
    std::shared_ptr<pcpp::IPv4Address> getDnsV4Addr() const { return dnsV4Address; }
    void setDnsV4Addr(const std::shared_ptr<pcpp::IPv4Address> v4Addr) { dnsV4Address = v4Addr; }
    std::shared_ptr<pcpp::IPv6Address> getDnsV6Addr() const { return dnsV6Address; }
    void setDnsV6Addr(const std::shared_ptr<pcpp::IPv6Address> v6Addr) { dnsV6Address = v6Addr; }
    std::shared_ptr<uint16_t> getDnsPort() const { return dnsPort; }
    void setDnsPort(std::shared_ptr<uint16_t> port) { dnsPort = port; }
    const std::string &getInputFile() const { return inputFile; }
    void setInputFile(const std::string &file) { inputFile = file; }
    std::shared_ptr<pcpp::IPAddress::AddressType> getIpVersion() const { return ipVersion; }
    void setIpVersion(std::shared_ptr<pcpp::IPAddress::AddressType> version) { ipVersion = version; }
    const std::string &getOutputFile() const { return outputFile; }
    void setOutputFile(const std::string &file) { outputFile = file; }
    std::shared_ptr<uint8_t> getTtlDec() const { return ttlDec; }
    void setTtlDec(std::shared_ptr<uint8_t> dec) { ttlDec = dec; }
    std::shared_ptr<uint16_t> getVlan() const { return vlan; }
    void setVlan(std::shared_ptr<uint16_t> id) { vlan = id; }
  };

} // namespace pcapconvert
