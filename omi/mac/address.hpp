#ifndef OMI_MAC_ADDRESS_HPP_
#define OMI_MAC_ADDRESS_HPP_

#include <ostream>
#include <array>
#include <cstdint>

// Mac address

namespace omi::mac {
struct address {

    static constexpr size_t bytes = 6;
    using type = std::array<uint8_t, bytes>;

  ///// Construction //////////////

    // Default constructor
    constexpr address()
      : value{ 0 } {} // Is this right?

    // Standard constructor
    explicit constexpr address(const type &value)
      : value{ value } {}

  ///// Methods ///////////////////

    // Cast operator
    explicit operator type() const {
        return value;
    }

    // Return value
    type get() const {
        return value; // Might be an issue with types
    }

    /*
    // Return value
    std::string text() const {
        return value; // Might be an issue with types
    }
    */
  //// Properties /////////////////

  // text

      type value;
};

///////////////////////////////////////////////

// Equals operator
inline bool operator==(const address& lhs, const address& rhs) {
    return lhs.get() == rhs.get();
}

// Not equals operator
inline bool operator!=(const address& lhs, const address& rhs) {
    return not operator==(lhs, rhs);
}

// Less than operator
inline bool operator<(const address& lhs, const address& rhs) {
    return lhs.get() < rhs.get();
}

// Greater than operator
inline bool operator>(const address& lhs, const address& rhs) {
    return operator<(rhs, lhs);
}

// Less than or equals operator
inline bool operator<=(const address& lhs, const address& rhs) {
    return not operator>(lhs, rhs);
}

// Greater than or equals operator
inline bool operator>=(const address& lhs, const address& rhs) {
    return not operator<(lhs, rhs);
}

/////

// need hash

///////////////////////////////////////////////

namespace translate { 

    constexpr static const char* octets[256] = {
        "00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "0a", "0b", "0c", "0d", "0e", "0f", "10", "11",
        "12", "13", "14", "15", "16", "17", "18", "19", "1a", "1b", "1c", "1d", "1e", "1f", "20", "21", "22", "23",
        "24", "25", "26", "27", "28", "29", "2a", "2b", "2c", "2d", "2e", "2f", "30", "31", "32", "33", "34", "35",
        "36", "37", "38", "39", "3a", "3b", "3c", "3d", "3e", "3f", "40", "41", "42", "43", "44", "45", "46", "47",
        "48", "49", "4a", "4b", "4c", "4d", "4e", "4f", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59",
        "5a", "5b", "5c", "5d", "5e", "5f", "60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "6a", "6b",
        "6c", "6d", "6e", "6f", "70", "71", "72", "73", "74", "75", "76", "77", "78", "79", "7a", "7b", "7c", "7d",
        "7e", "7f", "80", "81", "82", "83", "84", "85", "86", "87", "88", "89", "8a", "8b", "8c", "8d", "8e", "8f",
        "90", "91", "92", "93", "94", "95", "96", "97", "98", "99", "9a", "9b", "9c", "9d", "9e", "9f", "a0", "a1",
        "a2", "a3", "a4", "a5", "a6", "a7", "a8", "a9", "aa", "ab", "ac", "ad", "ae", "af", "b0", "b1", "b2", "b3",
        "b4", "b5", "b6", "b7", "b8", "b9", "ba", "bb", "bc", "bd", "be", "bf", "c0", "c1", "c2", "c3", "c4", "c5",
        "c6", "c7", "c8", "c9", "ca", "cb", "cc", "cd", "ce", "cf", "d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7",
        "d8", "d9", "da", "db", "dc", "dd", "de", "df", "e0", "e1", "e2", "e3", "e4", "e5", "e6", "e7", "e8", "e9",
        "ea", "eb", "ec", "ed", "ee", "ef", "f0", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "fa", "fb",
        "fc", "fd", "fe", "ff"
    };

   constexpr const char* octet(const uint8_t value) {
        return octets[value];
   }
}

// Stream operator
inline std::ostream &operator<<(std::ostream &out, const address &address) {
    return out << translate::octet(address.value[0]) << ':' // move this to text string
               << translate::octet(address.value[1]) << ':'
               << translate::octet(address.value[2]) << ':'
               << translate::octet(address.value[3]) << ':'
               << translate::octet(address.value[4]) << ':'
               << translate::octet(address.value[5]);
}

}

#endif