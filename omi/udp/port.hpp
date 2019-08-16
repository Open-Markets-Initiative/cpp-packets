#ifndef OMI_UDP_PORT_HPP_
#define OMI_UDP_PORT_HPP_

#include <cstdint>
#include <ostream>

#include <omi/byte/swap.hpp>

// Udp port

namespace omi::udp {

struct port {
    using type = std::uint16_t;
    static constexpr size_t size = sizeof(type);

    type data; 

  ///// Construction //////////////

    // Default constructor
    port()
      : data{ 0 } {}

    // Standard constructor
    explicit port(const type &value)
      : data{ value } {}

  ///// Properties ////////////////

    // Return port value
    [[nodiscard]] type value() const {
        return data;
    }

};

///////////////////////////////////////////////

// Stream operator
inline std::ostream& operator<<(std::ostream& out, const port& port) {
    return out << port.value();
}

}

namespace std {

template<> 
struct hash<omi::udp::port> {

    // Hash for udp port
    size_t operator()(const omi::udp::port& port) const noexcept {
        return std::hash<omi::udp::port::type>()(port.value()); // might be better to use underlying value
    }
};

}

#endif