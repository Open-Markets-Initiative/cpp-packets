#ifndef OMI_PCAP_FILE_HPP_
#define OMI_PCAP_FILE_HPP_

#include <ostream>
#include <fstream>
#include <vector>

#include <omi/pcap/header.hpp>
#include <omi/pcap/packet.hpp>
#include <omi/pcap/stream.hpp>

// Pcap packets

namespace omi::pcap {

struct file { // need to think about this name

  //// Member Variables ///////////

    pcap::header header;
    std::vector<pcap::packet> packets;

  //// Construction ///////////////

    // Construct from path
    explicit file(const std::string &path) {
        // throw exception if path is wrong?
        std::ifstream stream{ path, std::ios::binary };

        // throw exception if file is bad

        // read header
        stream.read(reinterpret_cast<char*>(&header), sizeof(pcap::header));

        // throw exception if file is not pcap

        // read packets
        while (stream.peek() != EOF) {
            packets.push_back(read::packet(stream));
        }
    }

  //// Methods ///////////////////

    // Is valid pcap file
    bool valid() const {
        return header.magic.valid();
    }

    // Is ethernet file?
    bool ethernet() const {
        return valid() and header.link.ethernet();
    }
};

// Stream operator
inline std::ostream &operator<<(std::ostream &out, const file &file) {
    return out; // TODO
}

}

#endif