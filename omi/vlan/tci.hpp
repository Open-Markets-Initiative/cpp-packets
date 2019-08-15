#ifndef OMI_VLAN_TCI_HPP_
#define OMI_VLAN_TCI_HPP_

#include <cstdint>
#include <ostream>

// Vlan tag control info

namespace omi::vlan {

struct tci {

    std::uint16_t pcp : 3;
    std::uint16_t dei : 1;
    std::uint16_t vid : 12;

  ///// Construction //////////////

    // Default constructor
    tci()
      : pcp{0}, dei{0}, vid{0}
    {}

   // Standard constructor
   // explicit tci(const underlying_type &value)
   //   : { value } {}



  //// Properties /////////////////
};


// Stream operator
inline std::ostream &operator<<(std::ostream &out, const vlan::tci &tci) {
    return out << "  pcp: " << tci.pcp << std::endl
               << "  dei: " << tci.dei << std::endl
               << "  vid: " << tci.vid;
}

}

#endif