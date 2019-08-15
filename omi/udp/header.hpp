#ifndef OMI_UDP_HEADER_HPP_
#define OMI_UDP_HEADER_HPP_

#include <omi/udp/port.hpp>
#include <omi/udp/length.hpp>

// Udp header

namespace omi::udp {

#pragma pack(push, 1)

struct header {

  //// Fields ///////////////

    udp::port source;         
    udp::port destination;
    udp::length length;
    //uint16_t checksum;

  //// Methods //////////////

    // Is packet valid?
    size_t valid() const {
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
    return out << "udp" << std::endl
               << frame.source << std::endl
               << frame.destination << std::endl
               << frame.length << std::endl;
}

}

#endif