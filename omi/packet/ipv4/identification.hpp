#ifndef OMI_IPV4_IDENTIFICATION_HPP_
#define OMI_IPV4_IDENTIFICATION_HPP_

#include <cstdint>
#include <ostream>

// Ipv4 identification

namespace omi::ipv4 {

struct identification {
    using type = uint16_t;

  ///// Construction //////////////

    // Default constructor
    identification()
      : value{ 0 } {}

    // Standard constructor
    explicit identification(const type &number)
      : value{ number } {}

  ///// Methods ///////////////////

    // Return value
    type get() const {
        return value; // Might be an issue with types
    }

  //// Properties /////////////////

      type value;
};

///////////////////////////////////////////////

// Equals operator
inline bool operator==(const identification& lhs, const identification& rhs) {
    return lhs.get() == rhs.get();
}

// Not equals operator
inline bool operator!=(const identification& lhs, const identification& rhs) {
    return not operator==(lhs, rhs);
}

///////////////////////////////////////////////

// Stream operator
inline std::ostream &operator<<(std::ostream &out, const identification &identification) {
    return out << identification.get();
}

}

#endif