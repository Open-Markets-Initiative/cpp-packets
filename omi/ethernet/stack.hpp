#ifndef OMI_ETHERNET_STACK_HPP_
#define OMI_ETHERNET_STACK_HPP_

#include <ostream>
#include <iso646.h>

#include <omi/ethernet/type.hpp>
#include <omi/byte/swap.hpp>


// Ethernet Info (Type or Size)

namespace omi {
namespace ethernet {

struct stack {

  ///// Properties //////////////

    ethernet::info info;       // Ethernet Payload Type or Size
    const char * payload;

  ///// Construction //////////////

    // Standard constructor
    explicit stack(const ethernet::info &info, const char * payload)
      : info{ info }, payload{ payload } {}

  ///// Methods ///////////////////


  //// Properties /////////////////

    bytes type() const {
        const auto translation = endian::little(value);
        return translation > 1500 ? translation : 0; // return a type
    }

};

///////////////////////////////////////////////


///////////////////////////////////////////////

// Stream operator
inline std::ostream &operator<<(std::ostream &out, const info &info) {
    return out; // << number.get();
}

} }

#endif