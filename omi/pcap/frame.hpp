#ifndef OMI_PCAP_FRAME_HPP_
#define OMI_PCAP_FRAME_HPP_

#include <omi/pcap/timestamp.hpp>
#include <omi/pcap/length.hpp>

// Pcap frame

namespace omi::pcap {

#pragma pack(push, 1)

struct frame {

  //// Fields ///////////////

    pcap::timestamp timestamp; // frame timestamp
    pcap::length length;       // number of octets of packet saved in file
    pcap::length packet;       // actual length of packet

  //// Methods //////////////

    // Read byte stream as frame
    static const frame* parse(const std::byte* buffer) {
        return reinterpret_cast<const frame*>(buffer);
    }

    // Read byte stream as pcap frame
    static frame* parse(std::byte* buffer) {
        return reinterpret_cast<frame*>(buffer);
    }

    // Return payload size in bytes
    [[nodiscard]] size_t size() const {
        return length.get();
    }

    // Is packet valid?
    [[nodiscard]] size_t valid() const {
        return length.get() > 0;
    }

	// Advance byte stream
	static void advance(std::byte* &buffer) {
		buffer += sizeof(frame);
	}

    // Parse header and advance byte stream
    static const frame* decode(std::byte* &buffer) {
        const auto result = parse(buffer);
        buffer += sizeof(frame);
        return result;
    }

    // is this kind of thing useful?

    [[nodiscard]] std::byte* payload() const {
        return (std::byte*)(&*this) + sizeof(frame);
    }

    // Get address of next packet // move this out of here
    [[nodiscard]] std::byte* next() const {
        return (std::byte*)(&*this) + size() + sizeof(frame);
    }
};

#pragma pack(pop)

// Stream operator
inline std::ostream &operator<<(std::ostream &out, const frame &frame) {
    return out << frame.timestamp << " : " << frame.length << " bytes";
}

}

#endif