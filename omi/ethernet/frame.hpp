#ifndef OMI_ETHERNET_FRAME_HPP_
#define OMI_ETHERNET_FRAME_HPP_

#include <omi/mac/address.hpp>
#include <omi/ethernet/info.hpp>

// Ethernet frame

namespace omi::ethernet {

#pragma pack(push, 1)

struct frame { // Rename this header

  //// Fields ///////////////

    // Todo: preamble
    mac::address destination;
    mac::address source;
    ethernet::info info;
    char * payload;

  //// Methods //////////////

    // Does header have vlan?
    bool vlan() const {
        return info.vlan();
    }

/*
    // getting an advance is next thing to do
    static void advance(char* &buffer) {
        // skip vlans

        buffer += sizeof(header);
    }
*/
    // 
    static const frame* parse(const char* buffer) {
        return reinterpret_cast<const frame*>(buffer);
    }

};

#pragma pack(pop)

// Stream operator
inline std::ostream &operator<<(std::ostream &out, const frame &frame) {
    return out << "ethernet" << std::endl
               << "  destination " << frame.destination << std::endl
               << "  source      " << frame.source;
}

}

#endif