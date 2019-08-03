#ifndef OMI_IPV4_INFO_HPP_
#define OMI_IPV4_INFO_HPP_

#include <cstdint>
#include <ostream>

// Ipv4 info field

namespace omi::ipv4 {

struct info  {

  ///// Properties ////////////////

    using underlying_type = std::uint8_t;

    struct mask {
        static const underlying_type header = 0x0F;
        static const underlying_type version = 0xF0;
    };

    underlying_type value;

  ///// Construction //////////////

    // Default constructor
    constexpr info()
      : value{ 0 } {}

    // Standard constructor
    explicit constexpr info(const underlying_type &value)
      : value{ value } {}

  ///// Methods ///////////////////

    // Returns ipv4 header
    constexpr std::uint32_t header() const {
        return static_cast<std::uint32_t>(value & mask::header);
    }

    // Returns ipv4 version
    constexpr std::uint32_t version() const {
        return static_cast<std::uint32_t>(value & mask::version);
    }
};

///////////////////////////////////////////////

// Stream operator
inline std::ostream &operator<<(std::ostream &out, const info &info) {
    return out << "  info: " << std::endl
               << "    header " << info.header() << std::endl
               << "    version " << info.version();
}

}

#endif