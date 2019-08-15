#ifndef OMI_ETHERNET_HEADER_HPP_
#define OMI_ETHERNET_HEADER_HPP_

#include <omi/mac/address.hpp>
#include <omi/ethernet/info.hpp>

// Ethernet frame header

namespace omi::ethernet {

#pragma pack(push, 1)

struct header {

  //// Fields ///////////////

    // Todo: preamble
    mac::address destination;  // Destination Mac Address
    mac::address source;       // Source Mac Address 
    ethernet::info info;       // Ethernet Payload Type or Size

  //// Methods //////////////

    // Parse method
    static header* parse(std::byte* buffer) {
        return reinterpret_cast<header*>(buffer);
    }

    // Parse method
    static const header* parse(const std::byte* buffer) {
        return reinterpret_cast<const header*>(buffer);
    }

    // Advance byte stream
    static void advance(std::byte* &buffer) {
        buffer += sizeof(header);
    }

    // Parse header and advance byte stream
    static const header* decode(std::byte* &buffer) {
        const auto result = parse(buffer);
        advance(buffer);
        return result;
    }
};

#pragma pack(pop)

// Stream operator
inline std::ostream &operator<<(std::ostream &out, const header &header) {
    return out << "ethernet" << std::endl
               << "  destination " << header.destination << std::endl
               << "  source     " << header.source << std::endl
               << "  type       " << header.info;
}

}

#endif