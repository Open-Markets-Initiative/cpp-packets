#ifndef OMI_ERF_FRAME_HPP_
#define OMI_ERF_FRAME_HPP_

#include <omi/packet/erf/timestamp.hpp>
#include <omi/packet/erf/type.hpp>

// Erf record type

namespace omi {
namespace erf {

#pragma pack(push, 1)

struct frame {
  // https://wiki.wireshark.org/ERF

  //// Fields ///////////////

    erf::timestamp timestamp;
    erf::type type;               // Erf record type
    uint8_t flags;
    uint16_t rlen;
    uint16_t lctr;
    uint16_t wlen;
    uint8_t offset;          // Ethernet padding
    uint8_t res;

    size_t length() const {
        return 5; //ntohs(rlen);
    }

};

#pragma pack(pop)

/*
// Stream operator
inline std::ostream &operator<<(std::ostream &out, const delta &delta) {
    return out << delta.initial << ":" << delta.value; // TODO: use fixed precision here
}

*/

} }

#endif