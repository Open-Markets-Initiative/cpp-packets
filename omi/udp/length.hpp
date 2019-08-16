#ifndef OMI_UDP_LENGTH_HPP_
#define OMI_UDP_LENGTH_HPP_

#include <cstdint>
#include <ostream>
#include <iso646.h>

#include <omi/byte/swap.hpp>


namespace omi::udp {

struct length {

  //// Properties /////////////////

    using type = uint16_t;

    type data;

  ///// Construction //////////////

    // Default constructor
    constexpr  length()
      : data{ 0 } {}

    // Standard constructor
    explicit constexpr  length(const type &number)
      : data{ number } {}

  ///// Methods ///////////////////

    // Return value
    [[nodiscard]] type value() const {
        return byte::swap(data);
    }
};

///////////////////////////////////////////////

// Equals operator
inline bool operator==(const length& lhs, const length& rhs) {
    return lhs.value() == rhs.value();
}

// Not equals operator
inline bool operator!=(const length& lhs, const length& rhs) {
    return not operator==(lhs, rhs);
}

// Less than operator
inline bool operator<(const length& lhs, const length& rhs) {
    return lhs.value() < rhs.value();
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

// Stream operator
inline std::ostream &operator<<(std::ostream &out, const udp::length &length) {
    return out << length.value();
}

}

#endif