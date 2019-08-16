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
    constexpr address()
      : value{ 0 } {}

    // Standard constructor
    explicit constexpr address(const type &value)
      : value{ value } {}

    // ip const char* containing the dotted-notation address.
    //address(const char* ip = nullptr);

    //address(const std::string& ip);

    [[nodiscard]] type get() const {
        return value;
    }

};

// stream operator

// Stream operator
inline std::ostream& operator<<(std::ostream& out, const ipv4::address& address) {
    return out << address.get(); // need good formatting
}

}

namespace std {

// std hash
template<> 
struct hash<omi::ipv4::address> {
    size_t operator()(const omi::ipv4::address& address) const noexcept {
        return std::hash<omi::ipv4::address::type>()(address.get());
    }
};

}

#endif

