#ifndef OMI_PCAP_STREAM_HPP_
#define OMI_PCAP_STREAM_HPP_

#include <omi/pcap/packet.hpp>

#include <fstream>

// Read pacp stream

namespace omi::pcap::read {

// Parse next packet (maybe use >>
inline pcap::packet packet(std::ifstream& stream) {
    pcap::packet packet;
    stream.read(reinterpret_cast<char*>(&packet.frame), sizeof(pcap::frame));
    packet.payload = std::make_unique<char[]>(packet.size()); // does packet need a move constructor?
    stream.read(packet.payload.get(), packet.size());

    return packet;
};

}

#endif