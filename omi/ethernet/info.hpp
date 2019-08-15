#ifndef OMI_ETHERNET_INFO_HPP_
#define OMI_ETHERNET_INFO_HPP_

#include <omi/byte/swap.hpp>
#include <omi/ethernet/type.hpp>

// Ethernet Info (Type or Size)

namespace omi::ethernet {

struct info {
    using underlying_type = uint16_t;

    underlying_type value;

  ///// Construction //////////////

    // Default constructor
    constexpr info()
      : value{ 0 } {}

    // Standard constructor
    constexpr explicit info(const underlying_type &value)
      : value{ value } {}

  ///// Methods ///////////////////

    // Return value
    [[nodiscard]] underlying_type get() const {
        return byte::swap(value);
    }

  //// Properties /////////////////

    [[nodiscard]] size_t bytes() const { // is size_t right?
        const auto translation = get();
        return translation <= 1500 ? translation : 0;
    }

    [[nodiscard]] underlying_type type() const {
        const auto translation = get();
        return translation > 1500 ? translation : 0; // return a made up type
    }

    // Is ethernet type vlan?
    [[nodiscard]] bool vlan() const {
        return value == big::endian::type::vlan;
    }

    // Is ethernet type ipv4?
    [[nodiscard]] bool ipv4() const {
        return value == big::endian::type::ipv4;
    }
};

///////////////////////////////////////////////

// Equals operator
inline bool operator==(const info& lhs, const info& rhs) {
    return lhs.get() == rhs.get();
}

// Not equals operator
inline bool operator!=(const info& lhs, const info& rhs) {
    return not operator==(lhs, rhs);
}

///////////////////////////////////////////////

// Stream operator
inline std::ostream &operator<<(std::ostream &out, const info &info) {
    return out << info.get();
}

}

#endif