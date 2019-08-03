#ifndef OMI_MAPPED_FILE_MODE_
#define OMI_MAPPED_FILE_MODE_

#include <ostream>

namespace omi::mapped::file {

enum class mode {
    readonly,
    readwrite
};

// Format access mode as text 
inline const char * text(const mode mode) {
    switch(mode) {
    case mode::readonly:
        return "Read Only";
    case mode::readwrite:
        return "Read Write";
    default:
        return "INVALID (Mode)";
    }
}

// Stream operator
inline std::ostream &operator<<(std::ostream &out, const mode &mode) {
    return out << text(mode);
}

///////////////////////////////////////////////////////////
// Traits

namespace is {
    // Is mode readonly?
    constexpr bool readonly(const mode value) { return value == mode::readonly; }
}

namespace is {
    // Is mode readwrite?
    constexpr bool readwrite(const mode value) { return value == mode::readwrite; }
}

namespace is {
    // Is mode valid value?
    constexpr bool valid(const mode value) { return readonly(value) or readwrite(value); }
}

// Compile time writable option 
template<mode access>
using enable_if_writable = std::enable_if<is::readwrite(access)>;

}

#endif