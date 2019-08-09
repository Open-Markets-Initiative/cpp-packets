#ifndef OMI_BYTE_ARRAY_HPP_
#define OMI_BYTE_ARRAY_HPP_

#include <cstddef>
#include <array>

namespace omi {

template<typename...list>
std::array<std::byte, sizeof...(list)> bytes(list&& ... args) noexcept {
    return { std::byte(std::forward<list>(args))... };
}

}

#endif