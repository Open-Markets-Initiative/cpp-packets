#ifndef OMI_IPV4_LENGTH_HPP_
#define OMI_IPV4_LENGTH_HPP_

#include <cstdint>
#include <ostream>

#include <omi/byte/swap.hpp>

// Pcap length/size

namespace omi::ipv4 {

struct length {
    using type = uint16_t;

  ///// Construction //////////////

    // Default constructor
    constexpr length() noexcept
      : value{ 0 } {}

    // Standard constructor
    explicit constexpr length(const type &number)
      : value{ number } {}

  ///// Methods ///////////////////

    // Return value
    [[nodiscard]] type get() const {
        return byte::swap(value);
    }

  //// Properties /////////////////

  protected:
      type value;
};

///////////////////////////////////////////////

// Equals operator
inline bool operator==(const length& lhs, const length& rhs) {
    return lhs.get() == rhs.get();
}

// Not equals operator
inline bool operator!=(const length& lhs, const length& rhs) {
    return not operator==(lhs, rhs);
}

// Less than operator
inline bool operator<(const length& lhs, const length& rhs) {
    return lhs.get() < rhs.get();
}

// Greater than operator
inline bool operator>(const length& lhs, const length& rhs) {
    return operator<(rhs, lhs);
}

// Less than or equals operator
inline bool operator<=(const length& lhs, const length& rhs) {
    return not operator>(lhs, rhs);
}

// Greater than or equals operator
inline bool operator>=(const length& lhs, const length& rhs) {
    return not operator<(lhs, rhs);
}

///////////////////////////////////////////////

// need +/-

///////////////////////////////////////////////

// Stream operator
inline std::ostream &operator<<(std::ostream &out, const length &number) {
    return out << "  length: " << number.get();
}

}

#endif