#ifndef OMI_IPV4_TTL_HPP_
#define OMI_IPV4_TTL_HPP_

#include <cstdint>
#include <ostream>

// Ipv4 Time to Live

namespace omi::ipv4 {

struct ttl {
    using type = uint8_t;

  ///// Construction //////////////

    // Default constructor
    ttl()
      : value{ 0 } {}

    // Standard constructor
    explicit ttl(const type &number)
      : value{ number } {}

  ///// Methods ///////////////////

    // Cast operator
    explicit operator type() const {
        return value;
    }

    // Return value
    auto get() const {
        return value;
    }

  //// Properties /////////////////

  protected:
      type value;
};

///////////////////////////////////////////////

// Equals operator
inline bool operator==(const ttl& lhs, const ttl& rhs) {
    return lhs.get() == rhs.get();
}

// Not equals operator
inline bool operator!=(const ttl& lhs, const ttl& rhs) {
    return not operator==(lhs, rhs);
}

// Less than operator
inline bool operator<(const ttl& lhs, const ttl& rhs) {
    return lhs.get() < rhs.get();
}

// Greater than operator
inline bool operator>(const ttl& lhs, const ttl& rhs) {
    return operator<(rhs, lhs);
}

// Less than or equals operator
inline bool operator<=(const ttl& lhs, const ttl& rhs) {
    return not operator>(lhs, rhs);
}

// Greater than or equals operator
inline bool operator>=(const ttl& lhs, const ttl& rhs) {
    return not operator<(lhs, rhs);
}

///////////////////////////////////////////////

// need +/-

///////////////////////////////////////////////

// Stream operator
inline std::ostream &operator<<(std::ostream &out, const ipv4::ttl &ttl) {
    return out << "  ttl: " << static_cast<size_t>(ttl.get());
}

} 

#endif