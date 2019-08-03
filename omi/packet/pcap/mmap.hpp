#ifndef OMI_PCAP_MMAP_HPP_
#define OMI_PCAP_MMAP_HPP_

#include <omi/packet/pcap/header.hpp>
#include <omi/packet/pcap/packet.hpp>
#include <omi/mapped/file.hpp>

// Pcap packets

namespace omi::pcap {

struct map { // need to think about this name
    using mmap = mapped::file::readonly;

    struct frame_iterator {
        const pcap::frame* frame = nullptr;
        size_t index = 1;

      // construction

        explicit frame_iterator(mmap::const_pointer & begin) {
            auto current = begin;
            pcap::header::advance(current);
            frame = pcap::frame::parse(current);
        }

        explicit frame_iterator(mmap::const_pointer & begin, const size_t length) {
            frame = pcap::frame::parse(begin + length);
        }

      // operations

        bool operator==(const frame_iterator& other) const {
            return frame == other.frame;
        }

        bool operator!=(const frame_iterator& other) const {
            return not (*this == other);
        }

        frame_iterator &operator++() {
            frame = pcap::frame::parse(frame->next());
            index++;
            return *this;
        }

        const pcap::frame * operator*() const {
            return frame;
        }
    };

  //// Member Variables ///////////

    mmap file;

  //// Construction ///////////////

    // Construct from path
    explicit map(const std::string &path) : file{ path } {
        // Check that file is pcap
        const auto pcap = pcap::header::parse(file.data());
        if (not pcap->valid()) {
            throw std::invalid_argument("File is not pcap");
        }
        // add string/filesystem template
    }

  //// Methods ///////////////////


//https://stackoverflow.com/questions/7758580/writing-your-own-stl-container/7759622#7759622

    // Returns an iterator to the first requested byte or cend()
    frame_iterator begin() const noexcept {
        return frame_iterator(file.data());
    }

    // Returns an iterator after the last requested byte
    frame_iterator end() const noexcept {
        return frame_iterator(file.data(), file.length()); // hack use begin/end
    }
};

}

#endif