#ifndef OMI_MEMORY_FILE_WINDOWS_
#define OMI_MEMORY_FILE_WINDOWS_
#ifdef _WIN32

#include <Windows.h>

#include "mode.hpp"
#include "paths.hpp"

namespace omi::mapped::file {

// Value to map entire file
enum { entire_file = 0 };

namespace error {
// Report valid operation (no error)
static const std::error_code none = std::error_code{};

// Returns last system error code
inline std::error_code last() noexcept {
    std::error_code error;
    error.assign(GetLastError(), std::system_category());
    return error;
}}

namespace bytes {
// Returns 4 high bytes of an int64_t
inline DWORD high(const int64_t bytes) noexcept {
    return bytes >> 32;
}

// Returns 4 low bytes of an int64_t
inline DWORD low(const int64_t bytes) noexcept {
    return bytes & 0xffffffff;
}}

namespace page {
// Returns the os page allocation granularity.
inline size_t size() {
    static const size_t size = [] {
        SYSTEM_INFO SystemInfo;
        GetSystemInfo(&SystemInfo);
        return SystemInfo.dwAllocationGranularity;
    }();
    return size;
}

// Align to the operating system page size for the nearest page boundary before `offset`
inline size_t align(size_t offset) noexcept {
    const auto page = size();
    return offset / page * page;
}}

// Windows memory map file implementation
template<typename byte_type> 
struct mmap {

    using value_type = byte_type; // this is overkill
    using size_type = int64_t;
    using handle_type = HANDLE; // Windows uses HANDLE
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;

    static_assert(sizeof(byte_type) == sizeof(char), "byte type must be the same size as char");

  // Construction /////////////////

    // Default constructor
    mmap() = default;

    // Disable copy constructor and assignment
    mmap(const mmap&) = delete;
    mmap& operator=(const mmap&) = delete;

    // Move constructor
    mmap(mmap<byte_type>&& other) noexcept
      : file{ std::move(other.file) },
        mapping{ std::move(other.mapping) }
    {   other.clear(); }

    // Move assignment
    mmap<byte_type>& operator=(mmap<byte_type>&& other) noexcept {
        if (this != &other) {
            // Remove the existing mapping
            unmap();

            // Move components
            file = std::move(other.file);
            mapping = std::move(other.mapping);

            // Destructor will unmap the mapping that was just moved here
            other.clear();
        }
        return *this;
    }

    // Destructor
    ~mmap() {
        unmap();
    }

  // Properties /////////////////

    // Returns windows handle to file
    handle_type file_handle() const noexcept {
        return file.handle;
    }

    // Returns mapping handle to file
    handle_type mapping_handle() const noexcept {
        return mapping.handle;
    }

    // Is file actively mapped?
    bool open() const noexcept {
        return valid(file.handle);
    }

    // Is file empty?
    bool empty() const noexcept {
        return length() == 0;
    }

    size_type offset() const noexcept {
        return mapping.length - file.length;
    }

    size_type length() const noexcept{
        return file.length;
    }

    size_type mapped_length() const noexcept {
        return mapping.length;
    }

  // Data Pointers ////////////////

    pointer data() noexcept { return file.data; }
    const_pointer data() const noexcept { return file.data; }

    // Index methods...no bounds checking 
    reference operator[](const size_type index) noexcept { return file.data[index]; }
    const_reference operator[](const size_type index) const noexcept { return file.data[index]; }

  // Methods //////////////////////

    // Map file from path
    template<typename path_type>
    std::error_code map(const path_type& path, size_type offset, size_type length, mode mode) {
        // Verify path
        if (is::empty(path)) {
            return std::make_error_code(std::errc::invalid_argument);
        }
        // Create file
        const auto handle = ::CreateFile(
            convert(path),
            is::readonly(mode) ? GENERIC_READ : GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            nullptr,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            nullptr);
        if (handle == INVALID_HANDLE_VALUE) {
            return error::last();
        }
        // Map file
        auto error = map(handle, offset, length, mode);
        if (error) {
            return error;
        }

        // Instance "owns" any mapping created from path
        mapping.owner = true;
        return error::none;
    }

    // Map file from handle
    std::error_code map(handle_type file_handle, size_type offset, size_type length, mode mode) {
        // Verify handle exists
        if (not valid(file_handle)) {
            return std::make_error_code(std::errc::bad_file_descriptor);
        }
        // Query file size
        LARGE_INTEGER size;
        if (::GetFileSizeEx(file_handle, &size) == 0) {
            return error::last();
        }
        const auto file_size = static_cast<int64_t>(size.QuadPart);
        if (length <= entire_file) {
            length = file_size;
        } else if (offset + length > file_size) {
            return std::make_error_code(std::errc::invalid_argument);
        }

        // Calculate mapping
        const auto aligned_offset = static_cast<int64_t>(page::align(offset));
        const auto mapping_length = offset - aligned_offset + length;
        const auto max_file_size = offset + length;

        const auto mapping_handle = ::CreateFileMapping(
            file_handle,
            nullptr,
            is::readonly(mode) ? PAGE_READONLY : PAGE_READWRITE,
            bytes::high(max_file_size),
            bytes::low(max_file_size),
            nullptr);
        if (not valid(mapping_handle)) {
            return error::last();
        }

        const auto mapping_start = static_cast<char*>(::MapViewOfFile(
            mapping_handle,
            is::readonly(mode) ? FILE_MAP_READ : FILE_MAP_WRITE,
            bytes::high(aligned_offset),
            bytes::low(aligned_offset),
            mapping_length));
        if (mapping_start == nullptr) {
            return error::last();
        }

        // Unmap the previous mapping that may have existed prior to this call
        unmap();
        // Set fields
        file.data = reinterpret_cast<pointer>(mapping_start + offset - aligned_offset);
        file.handle = file_handle;
        file.length = length;
        mapping.length = mapping_length;
        mapping.handle = mapping_handle;
        mapping.owner = false; // false until rest to true in map(handle)

        return error::none;
    }

    // Unmap file
    std::error_code unmap() {
        if (not open()) {
            return std::make_error_code(std::errc::bad_file_descriptor);
        }

        // Unmap handle
        if (valid(mapping.handle)) {
            ::UnmapViewOfFile(mapping_start());
            ::CloseHandle(mapping.handle);
            mapping.handle = INVALID_HANDLE_VALUE;
        }
        // Should check for error here?

        // Only close maps that instance owns
        if (mapping.owner) {
            ::CloseHandle(file.handle);
        }

        // Reset fields to their default values
        clear();
        return error::none;
    }

    // Sync file to disk
    std::error_code sync() {
        // Verify file is open
        if (not open()) {
            return std::make_error_code(std::errc::bad_file_descriptor);
        }
        // Flush mapping if data exists
        if (data() != nullptr) {
            if (::FlushViewOfFile(mapping_start(), mapping.length) == 0) {
                return error::last();
            }
        }
        // Flush buffers
        if (::FlushFileBuffers(file.handle) == 0) {
            return error::last();
        }

        return error::none;
    }

    // Swap
    void swap(mmap<byte_type>& other) noexcept {
        if (this == &other) { return; }

        std::swap(file.data, other.file.data);
        std::swap(file.handle, other.file.handle);
        std::swap(file.length, other.file.length);
        std::swap(mapping.handle, other.mapping.handle);
        std::swap(mapping.length, other.mapping.length);
        std::swap(mapping.owner, other.mapping.owner);
    }

  private:
  // Implementation ///////////////

    // Returns start of mapping
    pointer mapping_start() noexcept {
        return data() ? data() - offset() : nullptr;
    }

    // Is handle valid?
    static bool valid(const handle_type handle) noexcept {
        return handle != INVALID_HANDLE_VALUE and handle != nullptr;
    }

    // Clear data members
    void clear() noexcept {
        file.data = nullptr;
        file.handle = INVALID_HANDLE_VALUE;
        file.length = 0;
        mapping.length = 0;
        mapping.handle = INVALID_HANDLE_VALUE;
        mapping.owner = false;
    }

  // Data /////////////////////

    struct file {
        pointer data = nullptr;                    // For Windows, a file handle is required to retrieve a mapping handle
        handle_type handle = INVALID_HANDLE_VALUE; // Windows file handle
        size_type length = 0;                      // Requested length in bytes: may not be the length of the full mapping
    } file;
    struct mapping {
        handle_type handle = INVALID_HANDLE_VALUE; // Operations on the mapped region must be done using the mapping handle
        size_type length = 0;                      // Length of the full mapping
        bool owner = false;                        // This flag is used to determine when to close file handle
    } mapping ;
};

///////////////////////////////////////////////
// Operators

template<typename type>
bool operator==(const mmap<type>& lhs, const mmap<type>& rhs) {
    return lhs.data() == rhs.data() && lhs.length() == rhs.length();
}

template<typename type>
bool operator!=(const mmap<type>& lhs, const mmap<type>& rhs) {
    return !(lhs == rhs);
}

template<typename type>
bool operator<(const mmap<type>& lhs, const mmap<type>& rhs) {
    if (lhs.data() == rhs.data()) { return lhs.length() < rhs.length(); }
    return lhs.data() < rhs.data();
}

template<typename type>
bool operator<=(const mmap<type>& lhs, const mmap<type>& rhs) {
    return !(lhs > rhs);
}

template<typename type>
bool operator>(const mmap<type>& lhs, const mmap<type>& rhs) {
    if (lhs.data() == rhs.data()) { return lhs.length() > rhs.size(); }
    return lhs.data() > rhs.data();
}

template<typename type>
bool operator>=(const mmap<type>& lhs, const mmap<type>& rhs) {
    return !(lhs < rhs);
}

}

#endif
#endif