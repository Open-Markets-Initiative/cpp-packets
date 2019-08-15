#ifndef OMI_PCAP_LINK_HPP_
#define OMI_PCAP_LINK_HPP_

#include <cstdint>
#include <ostream>
#include <iso646.h>

#include <omi/pcap/type.hpp>

// Pcap file magic number

namespace omi::pcap {

struct link {
    using type = uint32_t;

  ///// Construction //////////////

    // Default constructor
    constexpr link() noexcept
      : value{ pcap::type::none } {}

    // Standard constructor
    constexpr explicit link(const type &value)
      : value{ value } {}

  ///// Methods ///////////////////

    // Return underlying value
    [[nodiscard]] type get() const {
        return value;
    }

    // Is pcap file ethernet layer capture?
    [[nodiscard]] bool ethernet() const {
        return value == pcap::type::ethernet;
    }

  //// Properties /////////////////

  protected:
      type value;
};

///////////////////////////////////////////////

// Equals operator
inline bool operator==(const link& lhs, const link& rhs) {
    return lhs.get() == rhs.get();
}

// Not equals operator
inline bool operator!=(const link& lhs, const link& rhs) {
    return not operator==(lhs, rhs);
}

///////////////////////////////////////////////

// Stream operator
inline std::ostream &operator<<(std::ostream &out, const link &number) {
    return out; // todo
}

}

#endif