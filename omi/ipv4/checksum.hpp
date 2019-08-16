#ifndef OMI_IPV4_CHECKSUM_HPP_
#define OMI_IPV4_CHECKSUM_HPP_

#include <cstdint>
#include <functional>
#include <ostream>

// Ipv4 Checksum

namespace omi::ipv4 {

struct checksum {
    using type = std::uint16_t;

    static constexpr size_t size = sizeof(type);

    type value; 

  ///// Construction //////////////

    // Default constructor
    constexpr checksum()
      : value{ 0 } {}

    // Standard constructor
    explicit constexpr checksum(const type &value)
      : value{ value } {}


    explicit operator type() const {
        return value;
    }

};

// Stream operator


}

#endif