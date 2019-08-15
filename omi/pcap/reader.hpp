#ifndef OMI_PCAP_READER_HPP_
#define OMI_PCAP_READER_HPP_

#include <omi/pcap/header.hpp>
#include <omi/pcap/packet.hpp>

#include <ostream>
#include <fstream>
#include <vector>

// Pcap file reader

namespace omi::pcap {

struct reader {

  //// Member Variables ///////////

    std::ifstream stream;
    pcap::header header;

  //// Construction ///////////////

    // Construct from path
    explicit reader(std::string path) {
        // throw exception if path is wrong?

        stream = std::ifstream{ path, std::ios::binary };
        stream.read(reinterpret_cast<char*>(&header), sizeof(omi::pcap::header));
    }

  //// Methods ///////////////////

    // Is this right?
    bool valid() const {
        return header.magic.valid() and not stream.bad() and not stream.eof();
    }

    bool more() {
        return header.magic.valid() and stream.peek() != EOF;
    }

    // Get next packet
    pcap::packet next() {
        pcap::packet packet;
        if (valid()) {
            stream.read(reinterpret_cast<char*>(&packet.frame), sizeof(omi::pcap::frame));
            packet.payload = std::make_unique<char[]>(packet.size());
            stream.read(packet.payload.get(), packet.size());
        }

        return packet;
    }

    // Get next packet
    bool get(pcap::packet& packet) {
        if (more()) {
            stream.read(reinterpret_cast<char*>(&packet.frame), sizeof(pcap::frame));
            packet.payload = std::make_unique<char[]>(packet.size());
            stream.read(packet.payload.get(), packet.size());
            return true;
        }

        return false;
    }

    // Get all packets in pcap
    auto packets() {
        std::vector<pcap::packet> packets;
        pcap::packet packet;
        while (get(packet)) {
            packets.push_back(std::move(packet));
        }

        return packets;
    }


};

}

#endif