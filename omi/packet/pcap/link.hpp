#ifndef OMI_PCAP_LINK_HPP_
#define OMI_PCAP_LINK_HPP_

#include <cstdint>

// Pcap link layer

namespace omi::pcap {

enum class link : std::uint32_t {
    ethernet = 1 // look into this
};


/*
// Stream operator
inline std::ostream &operator<<(std::ostream &out, const delta &delta) {
    return out
}

*/

}

#endif