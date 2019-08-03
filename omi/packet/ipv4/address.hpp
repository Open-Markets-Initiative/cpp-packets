#ifndef OMI_IPV4_ADDRESS_HPP_
#define OMI_IPV4_ADDRESS_HPP_

#include <cstdint>
#include <functional>
#include <ostream>

// Ipv4 Address

namespace omi::ipv4 {

struct address {
    using type = std::uint32_t;
    static constexpr size_t size = sizeof(type);

    type value; 

  ///// Construction //////////////

    // Default constructor
    address()
      : value{ 0 } {}

    // Standard constructor
    explicit address(const type &value)
      : value{ value } {}

    // ip const char* containing the dotted-notation address.
    //address(const char* ip = nullptr);

    //address(const std::string& ip);

    explicit operator type() const {
        return value;
    }

};

// stream operator


}

namespace std {

// std hash
template<> 
struct hash<omi::ipv4::address> {
    size_t operator()(const omi::ipv4::address& address) const {
        return std::hash<omi::ipv4::address::type>()(address);
    }
};

}

#endif

