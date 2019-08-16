#ifndef OMI_UDP_HEADER_HPP_
#define OMI_UDP_HEADER_HPP_

#include <omi/udp/port.hpp>
#include <omi/udp/length.hpp>
#include <omi/udp/checksum.hpp>

// Udp header

namespace omi::udp {

#pragma pack(push, 1)

struct header {

  //// Fields ///////////////

    udp::port source;         
    udp::port destination;
    udp::length length;
    udp::checksum checksum;

  //// Methods //////////////

    // Is valid udp?
    [[nodiscard]] bool valid() const {
        return true;
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
        buffer += sizeof(header);
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
inline std::ostream &operator<<(std::ostream &out, const udp::header &udp) {
    return out << "udp" << std::endl
               << "  source port: " << udp.source << std::endl
               << "  destination port: " << udp.destination << std::endl
               << "  length: " << udp.length;
               // add checksum
}

}

#endif