#ifndef OMI_PCAP_VERSION_HPP_
#define OMI_PCAP_VERSION_HPP_

#include <ostream>
#include <cstdint>

// Pcap file version

namespace omi::pcap {

#pragma pack(push, 1)

struct version {
    //0x04000200 // make these defaults

  //// Member Variables ///////////

    uint16_t major;          // Major version
    uint16_t minor;          // Minor version

  ///// Construction //////////////

    // Default constructor
    constexpr version() noexcept
        : major{ 0 }, minor{ 0 } {}

    // Standard constructor
    constexpr explicit version(const uint16_t& major, const uint16_t& minor)
        : major{ major }, minor{ minor } {}

  //// Methods ////////////////////

};

#pragma pack(pop)

// Stream operator
inline std::ostream &operator<<(std::ostream &out, const version &version) {
    return out << version.major << ',' << version.minor;
}

}

#endif