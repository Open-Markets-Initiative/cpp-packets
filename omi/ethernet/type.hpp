#ifndef OMI_ETHERNET_TYPE_HPP_
#define OMI_ETHERNET_TYPE_HPP_

#include <cstdint>

// Ethernet Type

namespace omi::ethernet {

// make this enum?
namespace type {
    static constexpr uint16_t ipv4 = 0x0800;
    static constexpr uint16_t ipv6 = 0xDD86;
    static constexpr uint16_t vlan = 0x8100;
}

// make big endian version
namespace big::endian::type {
    static constexpr uint16_t ipv4 = 0x0008;
    static constexpr uint16_t ipv6 = 0x86DD;
    static constexpr uint16_t vlan = 0x0081;
}

}

#endif