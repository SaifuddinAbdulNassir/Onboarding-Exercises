#pragma once 

// Standard includes
#include <cstdint>
#include <string>

// Library includes
#include <ndpi/ndpi_api.h>

namespace ndpi
{

  class ConnectionInfo 
  {
    private:
      // Data
      std::string category;
      std::string domain;
      bool done;
      ndpi_flow_struct *flow;
      uint32_t packetCount;
      std::string protocol;
      uint64_t uid;

    public:
    // Constructors & destructors
      ConnectionInfo();
      virtual ~ConnectionInfo();

    // Getters & setters
      const std::string& getCategory() const { return category; }
      const std::string& getDomain() const { return domain; }
      ndpi_flow_struct* getFlow() const { return flow; }
      uint32_t getPacketCount() const { return packetCount; }
      const std::string& getProtocol() const { return protocol; }
      uint64_t getUid() const { return uid; }
      bool isDone() const { return done; }
      void setCategory(const std::string &val) { category = val; }
      void setDomain(const std::string &val) { domain = val; }
      void setDone(bool val) { done = val; }
      void setFlow(ndpi_flow_struct *val) { if(val) flow = val; }
      void setPacketCount(uint32_t val) { packetCount = val; }
      void setProtocol(const std::string &val) { protocol = val; }
      void setUid(uint64_t val) { uid = val; }
  };

} // namespace ndpi
