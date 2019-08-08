#ifndef OMI_PCAP_HEADER_HPP_
#define OMI_PCAP_HEADER_HPP_

#include <cstddef>

#include <omi/packet/pcap/magic.hpp>
#include <omi/packet/pcap/version.hpp>
#include <omi/packet/pcap/length.hpp>
#include <omi/packet/pcap/timestamp.hpp>
#include <omi/packet/pcap/link.hpp>

// Pcap file header

namespace omi::pcap {

#pragma pack(push, 1)

struct header {

  //// Fields ///////////////

    pcap::magic magic;             // Pcap identifier (also timestamp precision)
    pcap::version version;         // Header version
    pcap::timestamp timestamp;     // Usually unused (0)
    pcap::length max;              // Max packet length 
    pcap::link link;               // Link layer type

  //// Methods //////////////

    // Is valid pcap file
    [[nodiscard]] bool valid() const noexcept {
        return magic.valid();
    }

    // Is ethernet file?
    [[nodiscard]] bool ethernet() const noexcept {
        return valid() and link.ethernet();
    }

  //// Decode ///////////////

    // Read byte stream as pcap file header
    static const header* parse(const std::byte* buffer) {
        return reinterpret_cast<const header*>(buffer);
    }

    // Read byte stream as pcap file header
    static header* parse(std::byte* buffer) {
        return reinterpret_cast<header*>(buffer);
    }

    // Advance byte stream
    static void advance(std::byte* &buffer) {
        buffer += sizeof(header);
    }

    // Advance byte stream
    static void advance(const std::byte*& buffer) {
        buffer += sizeof(header);
    }

    // Parse header and advance byte stream
    static const header* decode(const std::byte* &buffer) {
        const auto result = parse(buffer);
        buffer += sizeof(header);
        return result;
    }

    // Parse header and advance byte stream
    static header* decode(std::byte*& buffer) {
        const auto result = parse(buffer);
        buffer += sizeof(header);
        return result;
    }
};

#pragma pack(pop)

// Stream operator
inline std::ostream &operator<<(std::ostream &out, const header &file) {
    return out; // TODO
}

}

#endif