#ifndef OMI_PCAP_TYPE_HPP_
#define OMI_PCAP_TYPE_HPP_

#include <cstdint>

// Pcap capture type

namespace omi::pcap {

namespace type {
    static constexpr std::uint32_t none = 0x0000000;
    static constexpr std::uint32_t ethernet = 0x0000001; // IEEE 802.3 Ethernet
    static constexpr std::uint32_t erf = 0x00000C5;      // Extensible Record Format (ERF) 
}

}

#endif