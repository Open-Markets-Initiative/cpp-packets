#ifndef OMI_PCAP_MAGIC_HPP_
#define OMI_PCAP_MAGIC_HPP_

#include <cstdint>
#include <ostream>
#include <iso646.h>

// Pcap length/size

namespace omi::pcap {

struct magic {
    using type = uint32_t;

    static constexpr type number = 0xa1b2c3d4;

  ///// Construction //////////////

    // Default constructor
    magic()
      : value{ number } {}

    // Standard constructor
    explicit magic(const type &value)
      : value{ value } {}

  ///// Methods ///////////////////

    // Return underlying value
    type get() const {
        return value;
    }

    // Is magic number valid?
    bool valid() const {
        return value == number;
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