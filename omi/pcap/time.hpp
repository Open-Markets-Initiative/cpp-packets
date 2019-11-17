#ifndef OMI_PCAP_TIME_HPP_
#define OMI_PCAP_TIME_HPP_

#include <cstdint>
#include <ostream>

// Pcap time fields

namespace omi::pcap {

#pragma pack(push, 1)

struct time {

  //// Fields ///////////

    uint32_t zone;          // GMT to local correction
    uint32_t accuracy;      // Accuracy of timestamps

  ///// Construction //////////////

    // Default constructor
    constexpr time() noexcept
        : zone{ 0 }, accuracy{ 0 } {}
};

#pragma pack(pop)

// Stream operator
inline std::ostream &operator<<(std::ostream &out, const time &time) {
    return out << time.zone;
}

}

#endif