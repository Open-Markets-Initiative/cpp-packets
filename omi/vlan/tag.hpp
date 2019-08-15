#ifndef OMI_VLAN_TAG_HPP_
#define OMI_VLAN_TAG_HPP_

#include <omi/vlan/tci.hpp>
#include <omi/ethernet/info.hpp>

// Vlan frame

namespace omi::vlan {

#pragma pack(push, 1)

struct tag {

  //// Fields ///////////////

    vlan::tci tci;
    ethernet::info type; // rename this

  //// Methods //////////////

    // Parse method
    static tag* parse(std::byte* buffer) {
        return reinterpret_cast<tag*>(buffer);
    }

    // Parse method
    static const tag* parse(const std::byte* buffer) {
        return reinterpret_cast<const tag*>(buffer);
    }

    // Advance byte stream
    static void advance(std::byte* &buffer) {
        buffer += sizeof(tag);
    }

    // Parse vlan tag and advance byte stream
    static const tag* decode(std::byte* &buffer) {
        const auto result = parse(buffer);
        advance(buffer);
        return result;
    }

};

#pragma pack(pop)


// Stream operator
inline std::ostream &operator<<(std::ostream &out, const vlan::tag &vlan) {
    return out << "vlan" << std::endl
               << vlan.tci;
}


}

#endif