#ifndef OMI_IPV4_HEADER_HPP_
#define OMI_IPV4_HEADER_HPP_

#include <omi/ipv4/info.hpp>
#include <omi/ipv4/service.hpp>
#include <omi/ipv4/length.hpp>
#include <omi/ipv4/identification.hpp>
#include <omi/ipv4/fragment.hpp>
#include <omi/ipv4/ttl.hpp>
#include <omi/ipv4/protocol.hpp>
#include <omi/ipv4/checksum.hpp>
#include <omi/ipv4/address.hpp>

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
    ipv4::checksum checksum;
    ipv4::address source;
    ipv4::address destination;

  //// Methods //////////////

    // Is packet valid?
    [[nodiscard]] bool valid() const {
        return true;
    }

    // Has options?
    [[nodiscard]] bool options() const { // need to add another section
        return false;
    }

    // Parse method
    static header* parse(std::byte* buffer) {
        return reinterpret_cast<header*>(buffer);
    }

    // Parse method
    static const header* parse(const std::byte* buffer) {
        return reinterpret_cast<const header*>(buffer);
    }

    // Advance byte stream
    static void advance(std::byte*& buffer) {
        buffer += sizeof(header); // this is wrong need to pull from field
    }

    // Parse header and advance byte stream
    static const header* decode(std::byte*& buffer) {
        const auto result = parse(buffer);
        advance(buffer);
        return result;
    }
};

#pragma pack(pop)

// Stream operator
inline std::ostream &operator<<(std::ostream &out, const ipv4::header &frame) {
    return out << "ipv4" << std::endl
               << frame.info << std::endl
               << frame.service << std::endl
               << frame.length << std::endl
               << frame.fragment << std::endl
               << frame.ttl << std::endl
               << frame.protocol << std::endl
               // checksum
               << "  source address: " << frame.source << std::endl
               << "  destination address: " << frame.destination;
}

}

#endif