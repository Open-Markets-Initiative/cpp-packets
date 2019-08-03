#ifndef OMI_IPV4_PROTOCOL_HPP_
#define OMI_IPV4_PROTOCOL_HPP_

#include <cstdint>
#include <ostream>

// Ipv4 protocol

namespace omi::ipv4 {

struct protocol {
    using type = uint8_t;

  ///// Construction //////////////

    // Default constructor
    protocol()
      : value{ 0 } {}

    // Standard constructor
    explicit protocol(const type &number)
      : value{ number } {}

  ///// Methods ///////////////////

    // Return value
    type get() const {
        return value; // Might be an issue with types
    }

  //// Properties /////////////////

  protected:
      type value;
};

///////////////////////////////////////////////

// Equals operator
inline bool operator==(const protocol& lhs, const protocol& rhs) {
    return lhs.get() == rhs.get();
}

// Not equals operator
inline bool operator!=(const protocol& lhs, const protocol& rhs) {
    return not operator==(lhs, rhs);
}

// Less than operator
inline bool operator<(const protocol& lhs, const protocol& rhs) {
    return lhs.get() < rhs.get();
}

// Greater than operator
inline bool operator>(const protocol& lhs, const protocol& rhs) {
    return operator<(rhs, lhs);
}

// Less than or equals operator
inline bool operator<=(const protocol& lhs, const protocol& rhs) {
    return not operator>(lhs, rhs);
}

// Greater than or equals operator
inline bool operator>=(const protocol& lhs, const protocol& rhs) {
    return not operator<(lhs, rhs);
}

///////////////////////////////////////////////

// Stream operator
inline std::ostream &operator<<(std::ostream &out, const protocol &number) {
    return out << number.get();
}

}

#endif