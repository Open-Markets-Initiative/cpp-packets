#ifndef OMI_PCAP_MAGIC_HPP_
#define OMI_PCAP_MAGIC_HPP_

#include <cstdint>
#include <ostream>
#include <iso646.h>

// Pcap file magic number

namespace omi::pcap {

struct magic {
    using type = uint32_t;

    static constexpr type micros = 0xa1b2c3d4;
    static constexpr type nanos = 0xa1b23c4d;

  ///// Construction //////////////

    // Default constructor
    constexpr magic() noexcept
      : value{ micros } {}

    // Standard constructor
    constexpr explicit magic(const type &value)
      : value{ value } {}

  ///// Methods ///////////////////

    // Return underlying value
    [[nodiscard]] type get() const {
        return value;
    }

    // Is magic number valid?
    [[nodiscard]] bool valid() const {
        return value == micros or value == nanos;
    }

    // Are pcap timestamps in microseconds?
    [[nodiscard]] bool microseconds() const {
        return value == micros ;
    }

    // Are pcap timestamps in nanoseconds?
    [[nodiscard]] bool nanoseconds() const {
        return value == nanos;
    }

  //// Properties /////////////////

  protected:
      type value;
};

///////////////////////////////////////////////

// Equals operator
inline bool operator==(const magic& lhs, const magic& rhs) {
    return lhs.get() == rhs.get();
}

// Not equals operator
inline bool operator!=(const magic& lhs, const magic& rhs) {
    return not operator==(lhs, rhs);
}

///////////////////////////////////////////////

// Stream operator
inline std::ostream &operator<<(std::ostream &out, const magic &number) {
    return out << (number.valid() ? "Valid" : "Invalid");
}

}

#endif