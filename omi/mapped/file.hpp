#ifndef OMI_MAPPED_FILE_
#define OMI_MAPPED_FILE_

#include "file/basic.hpp"

namespace omi::mapped::file {

// Use for all read-only memory mapped files
using readonly = basic<mode::readonly, std::byte>;

// Use for all read-write memory mapped files
using readwrite = basic<mode::readwrite, std::byte>;

}

#endif