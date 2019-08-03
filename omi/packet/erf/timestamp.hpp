#ifndef OMI_ERF_TIMESTAMP_HPP_
#define OMI_ERF_TIMESTAMP_HPP_

#include <ostream>
#include <cstdint>

// Erf timestamp

namespace omi {
namespace erf {

#pragma pack(push, 1)

struct timestamp {

  //// Member Variables ///////////

    uint32_t fraction;       // Fractional seconds
    uint32_t seconds;        // Seconds since epoch

  //// Methods

    // Nanoseconds since unix epoch
    static constexpr uint64_t nanoseconds(const timestamp &timestamp) {
        return (uint64_t(timestamp.seconds) * 1000000000ull) + ((uint64_t(timestamp.fraction) * 1000000000ull + (1ull << 31)) >> 32);
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

} }

#endif