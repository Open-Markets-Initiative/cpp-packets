#ifndef OMI_IPV4_PROTOCOL_HPP_
#define OMI_IPV4_PROTOCOL_HPP_

#include <cstdint>
#include <ostream>

#include <omi/ipv4/type.hpp>

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
    [[nodiscard]] type get() const {
        return value;
    }

    // Is udp protocol
    [[nodiscard]] bool udp() const {
        return value == ipv4::type::udp;
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

///////////////////////////////////////////////

// Stream operator
inline std::ostream &operator<<(std::ostream &out, const protocol &number) {
    return out << "  protocol: " << static_cast<size_t>(number.get());
}

}

#endif