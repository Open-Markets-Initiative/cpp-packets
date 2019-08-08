#ifndef OMI_IPV4_HEADER_HPP_
#define OMI_IPV4_HEADER_HPP_

#include <omi/packet/ipv4/info.hpp>
#include <omi/packet/ipv4/service.hpp>
#include <omi/packet/ipv4/length.hpp>
#include <omi/packet/ipv4/identification.hpp>
#include <omi/packet/ipv4/fragment.hpp>
#include <omi/packet/ipv4/ttl.hpp>
#include <omi/packet/ipv4/protocol.hpp>

// Ipv4 header

namespace omi::ipv4 {

#pragma pack(push, 1)

struct header {

  //// Fields ///////////////

    ipv4::info info;         
    ipv4::service service;
    ipv4::length length;
    ipv4::identification identification;
    ipv4::fragment fragment;
    ipv4::ttl ttl;
    ipv4::protocol protocol;
    //uint16_t checksum;
  //ipv4::address source;
  //ipv4::address destination;
    // how to handle options? size?

  //// Methods //////////////

    // Is packet valid?
    bool valid() const {
        return true;
    }

    // 
    static const header* parse(const std::byte* buffer) {
        return reinterpret_cast<const header*>(buffer);
    }

    static header* parse(std::byte* buffer) {
        return reinterpret_cast<header*>(buffer);
    }
};

#pragma pack(pop)

// Stream operator
inline std::ostream &operator<<(std::ostream &out, const header &frame) {
    return out << "ipv4" << std::endl
               << frame.info << std::endl
               << frame.service << std::endl
               << frame.length << std::endl
               << frame.fragment << std::endl
               << frame.ttl << std::endl;
}

}

#endif