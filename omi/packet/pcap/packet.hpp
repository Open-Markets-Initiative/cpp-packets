#ifndef OMI_PCAP_PACKET_HPP_
#define OMI_PCAP_PACKET_HPP_

#include <omi/packet/pcap/frame.hpp>
#include <memory>

// Pcap packet (for persisting packet on heap)

namespace omi::pcap {

struct packet {

  //// Fields ///////////////

    pcap::frame frame;
    std::unique_ptr<char[]> payload;

  //// Methods //////////////

    packet() {}

    packet(packet&& other) noexcept 
       : frame{ other.frame }, payload{ std::move(other.payload)} {}  

  //// Methods //////////////

    // Return packet size in bytes
    size_t size() const {
        return frame.size();
    }

};

/*
// Stream operator
inline std::ostream &operator<<(std::ostream &out, const delta &delta) {
    return out << delta.initial << ":" << delta.value; // TODO: use fixed precision here
}

*/

}

#endif