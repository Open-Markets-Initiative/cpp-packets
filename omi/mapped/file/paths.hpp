#ifndef OMI_FILE_MAP_PATHS_
#define OMI_FILE_MAP_PATHS_

#include <type_traits>

namespace omi::mapped::file {

///////////////////////////////////
// Meta functions

// Enable if path type 
template<typename type>
using enable_if_char = std::enable_if_t<std::is_same<const char*, typename std::decay<type>::type>::value>;

// Enable if path type has empty() method
template<typename type>
using enable_if_empty = decltype(std::declval<type>().empty());

// Enable if path type has data() method
template<typename path>
using enable_if_data = decltype(std::declval<path>().data());

///////////////////////////////////
// Path Methods

// is::empty
namespace is {

// Is path empty for char type?
template<typename type,
    typename = enable_if_char<type>>
bool empty(type path) {
    return !path || (*path == 0);
}

// Is path empty?
template<typename type,
    typename = enable_if_empty<type>>
bool empty(const type& path) {
    return path.empty();
}

}

// Convert path type to char *
template<typename type,
    typename = enable_if_char<type>>
const char* convert(type path) {
    return path;
}

// Convert path type to char * from data() member
template<typename type,
    typename = enable_if_data<type>>
const char* convert(const type& path) {
    return path.data();
}

}

#endif