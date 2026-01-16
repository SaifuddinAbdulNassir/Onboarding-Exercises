#pragma once 

#include <cstdint>

struct ConnKey {
    uint32_t src_ip;
    uint32_t dst_ip;
    uint16_t src_port;
    uint16_t dst_port;
    uint8_t  l4_proto;

    bool operator==(const ConnKey& o) const {
        return src_ip == o.src_ip &&
               dst_ip == o.dst_ip &&
               src_port == o.src_port &&
               dst_port == o.dst_port &&
               l4_proto == o.l4_proto;
    }
};

struct ConnKeyHash {
    size_t operator()(const ConnKey& k) const {
        return std::hash<uint64_t>()(
            ((uint64_t)k.src_ip << 32) | k.dst_ip
        ) ^ (k.src_port << 16 | k.dst_port);
    }
};