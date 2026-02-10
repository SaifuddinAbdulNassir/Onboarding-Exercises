#pragma once

// Standard includes
#include <cstdint>
#include <string>

// Library includes
#include <ndpi/ndpi_api.h>

namespace ndpi
{

  class NdpiConnectionInfo
  {
  private:
    // Data
    std::string category = "";
    std::string domain = "";
    bool done = false;
    ndpi_flow_struct *flow = nullptr;
    size_t packetCount = 0;
    std::string protocol = "";
    size_t uid = 0;

  public:
    // Constructors & destructors
    NdpiConnectionInfo();
    virtual ~NdpiConnectionInfo();

    // Getters & setters
    const std::string &getCategory() const { return category; }
    void setCategory(const std::string &val) { category = val; }
    const std::string &getDomain() const { return domain; }
    void setDomain(const std::string &val) { domain = val; }
    bool getDone() const { return done; }
    void setDone(bool val) { done = val; }
    ndpi_flow_struct *getFlow() const { return flow; }
    void setFlow(ndpi_flow_struct *val) { val ? flow = val : flow = nullptr; }
    size_t getPacketCount() const { return packetCount; }
    void setPacketCount(size_t val) { packetCount = val; }
    const std::string &getProtocol() const { return protocol; }
    void setProtocol(const std::string &val) { protocol = val; }
    size_t getUid() const { return uid; }
    void setUid(size_t val) { uid = val; }
  };

} // namespace ndpi
