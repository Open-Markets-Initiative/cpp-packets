#ifndef OMI_IPV4_INFO_HPP_
#define OMI_IPV4_INFO_HPP_

#include <cstdint>
#include <ostream>

// Ipv4 info field

namespace omi::ipv4 {

struct info  {

  ///// Properties ////////////////

    using underlying_type = std::uint8_t;

    static const underlying_type header_mask = 0x0F;
    static const underlying_type version_mask = 0xF0;

    underlying_type data;

  ///// Construction //////////////

    // Default constructor
    constexpr info()
      : data{ 0 } {} // is this right value?

    // Standard constructor
    explicit constexpr info(const underlying_type &value)
      : data{ value } {}

  ///// Methods ///////////////////

    // Returns ipv4 header
    [[nodiscard]] constexpr std::uint32_t header() const {
        // Optimization for standard no option header
        if ((data & header_mask) == 5) { return 20; }

        return static_cast<std::uint32_t>(data & header_mask) * 4;
    }

    // Returns ipv4 version
    [[nodiscard]] constexpr std::uint32_t version() const {
        return static_cast<std::uint32_t>(data & version_mask) >> 4;
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