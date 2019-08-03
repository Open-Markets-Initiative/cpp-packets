#ifndef OMI_ENDIAN_LITTLE_HPP_
#define OMI_ENDIAN_LITTLE_HPP_

#include <cstdint>

// Pcap length/size

namespace omi::endian {

constexpr uint16_t little(const uint16_t & value) {
    return (static_cast<uint16_t>(value) & 0xFF) << 8 | 
           (static_cast<uint16_t>(value) & 0xFF00) >> 8;
}

constexpr uint32_t little(const uint32_t & value) {
    return (static_cast<uint32_t>(value) & 0x000000FF) << static_cast<uint32_t>(24) |
           (static_cast<uint32_t>(value) & 0x0000FF00) >> 8 |
           (static_cast<uint32_t>(value) & 0x00FF0000) << 8 |
           (static_cast<uint32_t>(value) & 0xFF000000) >> 24;
}

/*
constexpr uint64_t little(const uint64_t & value) {
    return (static_cast<uint64_t>(value) & 0xFF) << 24 |
           (static_cast<uint64_t>(value) & 0xFF00) << 8 |
           (static_cast<uint64_t>(value) & 0xFF0000) >> 8 |
           (static_cast<uint64_t>(value) & 0xFF000000) >> 24;
}
*/

}

#endif