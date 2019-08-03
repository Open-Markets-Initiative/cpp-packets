#ifndef OMI_MAPPED_FILE_
#define OMI_MAPPED_FILE_

#include "file/basic.hpp"

namespace omi::mapped::file {

// Use for all read-only memory mapped files...prefer over using mapped::file::basic
template<typename byte_type>
using read_only_memory_map_of = basic<mode::readonly, byte_type>;
using readonly = read_only_memory_map_of<std::byte>;

// Use for all read-write memory mapped files...prefer over using mapped::file::basic
template<typename byte_type>
using read_write_memory_map_of = basic<mode::readwrite, byte_type>;
using readwrite = read_write_memory_map_of<std::byte>;

}

#endif