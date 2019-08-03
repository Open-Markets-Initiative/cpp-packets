#ifndef OMI_PACKET_ERF_TYPE_HPP_
#define OMI_PACKET_ERF_TYPE_HPP_

#include <cstdint>

// Erf Record Type

namespace omi {
namespace erf {

enum class type : uint8_t {
    ethernet = 2
};


/*
// Stream operator
inline std::ostream &operator<<(std::ostream &out, const delta &delta) {
    return out
}

*/

} }

#endif