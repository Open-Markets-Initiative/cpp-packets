#ifndef OMI_IPV4_SERVICE_HPP_
#define OMI_IPV4_SERVICE_HPP_

#include <cstdint>
#include <ostream>

// Ipv4 Service

namespace omi::ipv4 {

struct service {
    using type = uint8_t;

    uint8_t dscp : 6;
    uint8_t ecn : 2;

  ///// Construction //////////////

    // Default constructor
    service()
      : dscp(0), ecn{0}
    {}

    // Standard constructor
   // explicit service(const type &value)
   //   : value{ value } {}

  ///// Methods ///////////////////

    // Todo: pull out components


};

///////////////////////////////////////////////

// Stream operator
inline std::ostream &operator<<(std::ostream &out, const service &service) {
    return out << "  service: " << std::endl
               << "    dscp: " << static_cast<std::uint32_t>(service.dscp) << std::endl
               << "    ecn:  " << static_cast<std::uint32_t>(service.ecn);
}

}

#endif