#ifndef OMI_PCAP_MAGIC_HPP_
#define OMI_PCAP_MAGIC_HPP_

#include <cstdint>
#include <ostream>
#include <iso646.h> // check build settings

// Pcap file magic number

namespace omi::pcap {

struct magic {
    using type = std::uint32_t;

    static constexpr type micros = 0xa1b2c3d4;
    static constexpr type nanos = 0xa1b23c4d;

  ///// Construction //////////////

    // Default constructor
    constexpr magic() noexcept
      : data{ micros } {}

    // Standard constructor
    constexpr explicit magic(const type &value)
      : data{ value } {}

  ///// Methods ///////////////////

    // Return underlying value
    [[nodiscard]] type value() const {
        return data;
    }

    // Is magic number valid?
    [[nodiscard]] bool valid() const {
        return data == micros or data == nanos;
    }

    // Are pcap timestamps in microseconds?
    [[nodiscard]] bool microseconds() const {
        return data == micros ;
    }

    // Are pcap timestamps in nanoseconds?
    [[nodiscard]] bool nanoseconds() const {
        return data == nanos;
    }

  //// Properties /////////////////

  protected:
      type data;
};

///////////////////////////////////////////////

// Equals operator
inline bool operator==(const magic& lhs, const magic& rhs) {
    return lhs.value() == rhs.value();
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