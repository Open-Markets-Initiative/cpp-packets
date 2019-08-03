#ifndef OMI_PCAP_LENGTH_HPP_
#define OMI_PCAP_LENGTH_HPP_

#include <cstdint>
#include <ostream>

// Pcap length/size

namespace omi::pcap {

struct length {
    using underlying_type = uint32_t;

  ///// Construction //////////////

    // Default constructor
    length()
      : value{ 0 } {}

    // Standard constructor
    explicit length(const underlying_type &number)
      : value{ number } {}

  ///// Methods ///////////////////

    // Return value
    underlying_type get() const {
        return value; // Might be an issue with types
    }

  //// Properties /////////////////

  protected:
    underlying_type value;
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
    return out << number.get();
}

}

#endif