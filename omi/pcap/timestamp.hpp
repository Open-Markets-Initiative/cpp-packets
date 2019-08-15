#ifndef OMI_PCAP_TIMESTAMP_HPP_
#define OMI_PCAP_TIMESTAMP_HPP_

#include <cstdint>
#include <ostream>
#include <iso646.h>

// Pcap timestamp

namespace omi::pcap {

#pragma pack(push, 1)

struct timestamp {

  //// Member Variables ///////////

    uint32_t seconds;        // Seconds
    uint32_t microseconds;   // Microseconds

  //// Methods ////////////////////

    // Is timestamp valid?
    bool valid() const {
        return seconds != 0 or microseconds != 0;
    }

  /////////////////////

    // Nanoseconds since unix epoch
    static constexpr uint64_t nanoseconds(const timestamp &timestamp) {
        return uint64_t(timestamp.seconds) * 1000000000ull + uint64_t(timestamp.microseconds) * 1000ull; // make these constants
    }

    // Nanoseconds since unix epoch
    uint64_t nanoseconds() const {
        return nanoseconds(*this);
    }
};

#pragma pack(pop)

// Stream operator
inline std::ostream &operator<<(std::ostream &out, const timestamp &timestamp) {
    return out << timestamp.nanoseconds();
}

}

#endif