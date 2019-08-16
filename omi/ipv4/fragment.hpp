#ifndef OMI_IPV4_FRAGMENT_HPP_
#define OMI_IPV4_FRAGMENT_HPP_

#include <cstdint>
#include <ostream>

// Ipv4 Fragment

namespace omi::ipv4 {

struct fragment {
    using type = std::uint16_t;

    struct mask {
        // Big endian
        static const type reserved = 0x80;
        static const type dont = 0x40;
        static const type more = 0x20;
        static const type offset = 0x0F; // best way to handle this across bytes?
    };

    type value;

  ///// Construction //////////////

    // Default constructor
    constexpr fragment()
      : value{ 0 } {}

    // Standard constructor
    explicit constexpr fragment(const type &value)
      : value{ value } {}

  ///// Methods ///////////////////

    // Returns ipv4 reserved fragment flag
    [[nodiscard]] constexpr bool reserved() const {
        return value & mask::reserved;
    }

    // Returns ipv4 don't fragment flag
    [[nodiscard]] constexpr bool dont() const {
        return value & mask::dont;
    }

    // Returns ipv4 more fragments flag
    [[nodiscard]] constexpr bool more() const {
        return value & mask::more;
    }

    // Returns ipv4 fragment offset (does not work)
    [[nodiscard]] constexpr std::size_t offset() const {
        return static_cast<std::size_t>(value & mask::offset);
    }
};

///////////////////////////////////////////////

// Stream operator
inline std::ostream &operator<<(std::ostream &out, const fragment &fragment) {
    return out << "  fragment:"  << std::endl
               << "    reserved: " << fragment.reserved() << std::endl
               << "    dont:     " << fragment.dont() << std::endl
               << "    more:     " << fragment.more() << std::endl
               << "    offset:   " << fragment.offset();
}

}

#endif