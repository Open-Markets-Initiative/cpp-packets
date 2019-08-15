#ifndef OMI_BYTE_SWAP_HPP_
#define OMI_BYTE_SWAP_HPP_

#include <cstdint>

namespace omi::byte {

// swap byte endian order for 2 bytes 
constexpr std::uint16_t swap(const std::uint16_t & value) {
    return (static_cast<std::uint16_t>(value) & 0x00FF) << 8 | 
           (static_cast<std::uint16_t>(value) & 0xFF00) >> 8;
}

// swap byte endian order for 4 bytes
constexpr std::uint32_t swap(const std::uint32_t & value) {
    return (static_cast<std::uint32_t>(value) & 0x000000FF) << 24 |
           (static_cast<std::uint32_t>(value) & 0x0000FF00) >> 8  |
           (static_cast<std::uint32_t>(value) & 0x00FF0000) << 8  |
           (static_cast<std::uint32_t>(value) & 0xFF000000) >> 24;
}

// swap byte endian order for 8 bytes
constexpr std::uint64_t swap(const std::uint64_t & value) { // untested
    return (static_cast<std::uint64_t>(value) & 0x00000000000000FF) << 56 |
           (static_cast<std::uint64_t>(value) & 0x000000000000FF00) >> 40 |
           (static_cast<std::uint64_t>(value) & 0x0000000000FF0000) >> 24 |
           (static_cast<std::uint64_t>(value) & 0x00000000FF000000) << 8  |
           (static_cast<std::uint64_t>(value) & 0x000000FF00000000) >> 8  |
           (static_cast<std::uint64_t>(value) & 0x0000FF0000000000) << 24 |
           (static_cast<std::uint64_t>(value) & 0x00FF000000000000) >> 40 |
           (static_cast<std::uint64_t>(value) & 0xFF00000000000000) << 56;
}

}

#endif