#ifndef OMI_UDP_PORT_HPP_
#define OMI_UDP_PORT_HPP_

#include <cstdint>
#include <ostream>

// Udp Port

namespace omi::udp {

struct port {
    using type = std::uint16_t;
    static constexpr size_t size = sizeof(type);

    type value; 

  ///// Construction //////////////

    // Default constructor
    port()
      : value{ 0 } {}

    // Standard constructor
    explicit port(const type &value)
      : value{ value } {}

    // Return underlying value
    type get() const {
        return value;
    }

};

///////////////////////////////////////////////

// Stream operator
inline std::ostream& operator<<(std::ostream& out, const port& port) {
    return out << port;// todo
}

}

namespace std {

// std hash for udp port
template<> 
struct hash<omi::udp::port> {
    size_t operator()(const omi::udp::port& port) const noexcept {
        return std::hash<omi::udp::port::type>()(port.get());
    }
};

}

#endif