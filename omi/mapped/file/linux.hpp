#ifndef OMI_FILE_MAP_LINUX_
#define OMI_FILE_MAP_LINUX_
#ifndef _WIN32

#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "mode.hpp"
#include "paths.hpp"

namespace omi::mapped::file {

#define INVALID_HANDLE_VALUE -1

// Where does this belong?
enum { entire_file = 0 };

namespace error {
// Report valid operation (no error)
static const std::error_code none = std::error_code();

// Returns last system error code
inline std::error_code last() noexcept {
    std::error_code error;
      error.assign(errno, std::system_category());
    return error;
}}


namespace page {
// Store system page size
inline size_t size() {
    static const size_t size = [] { return sysconf(_SC_PAGE_SIZE); }();
    return size;
}

// Align `offset` to the operating system page size and the nearest page boundary before `offset`
inline size_t aligned(size_t offset) noexcept {
    // Integer division rounds down to the page alignment
    const auto page = size();
    return offset / page * page;
}}

// Linux memory map file implementation
template<typename byte_type> 
struct mmap {
    static_assert(sizeof(byte_type) == sizeof(char), "byte type must be the same size as char");

    using value_type = byte_type; // this is overkill
    using size_type = int64_t;
    using handle_type = int; // Linux uses int for handle type
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;

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
    { other.clear(); }

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

    handle_type file_handle() const noexcept {
        return file.handle;
    }

    // Returns same as file_handle() on linux
    handle_type mapping_handle() const noexcept {
        return file.handle;
    }

    // Is file actively mapped?
    bool open() const noexcept {
        return file.handle != INVALID_HANDLE_VALUE;
    }

    // Is file empty?
    bool empty() const noexcept {
        return length() == 0;
    }

    // Mapping offset
    size_type offset() const noexcept {
        return mapping.length - file.length;
    }

    // File length
    size_type length() const noexcept {
        return file.length;
    }

    // Mapped length
    size_type mapped_length() const noexcept {
        return mapping.length;
    }

  // Data Pointers ////////////////

    // File data handle accessors
    pointer data() noexcept { return file.data; }
    const_pointer data() const noexcept { return file.data; }

    // Index methods...no bounds checking 
    reference operator[](const size_type index) noexcept { return file.data[index]; }
    const_reference operator[](const size_type index) const noexcept { return file.data[index]; }

  // Methods //////////////////////

    // Map file from path 
    template<typename path_type>
    std::error_code map(path_type& path, size_type offset, size_type length, mode mode) {
        // Verify path
        if (is::empty(path)) {
            return std::make_error_code(std::errc::invalid_argument);
        }
        // Open file handle
        const auto handle = ::open(convert(path), is::readonly(mode) ? O_RDONLY : O_RDWR);
        if (handle == INVALID_HANDLE_VALUE) {
            return error::last();
        }
        // Map file
        auto error = map(handle, offset, length, mode);
        if (error) {
            return error;
        }

        // Declare ownership...must be after map()
        mapping.owner = true;
        return error::none;
    }

    // Map file from existing handle
    std::error_code map(handle_type handle, size_type offset, size_type length, mode mode) {
        // Verify handle  
        if (handle == INVALID_HANDLE_VALUE) {
            return std::make_error_code(std::errc::bad_file_descriptor);
        }
        
        // Query file size
        struct stat buffer;
        if (::fstat(handle, &buffer) == -1) {
            return error::last();
        }
        // Calculate mapping
        const auto file_size = buffer.st_size;
        if (length <= entire_file) {
            length = file_size;
        } else if (offset + length > file_size) {
            return std::make_error_code(std::errc::invalid_argument);
        }
        const int64_t aligned_offset = page::aligned(offset);
        const int64_t length_to_map = offset - aligned_offset + length;

        // Map handle
        auto mapping_start = static_cast<char*>(::mmap(
            0, 
            length_to_map,
            is::readonly(mode) ? PROT_READ : PROT_WRITE,
            MAP_SHARED,
            handle,
            aligned_offset));
        if (mapping_start == MAP_FAILED) {
            return error::last();
        }

        // Unmap the previous mapping that may have existed prior to this call
        unmap(); // should return this value?

        // set data
        file.handle = handle;
        file.data = reinterpret_cast<pointer>(mapping_start + offset - aligned_offset);
        file.length = length;
        mapping.length = length_to_map;
        mapping.owner = false;

        return error::none;
    }

    // Unmap file
    std::error_code unmap() {
        // Verify file is open
        if (not open()) { 
            return std::make_error_code(std::errc::bad_file_descriptor);
        }
        // Unmap file handle
        if (data() != nullptr) {
            ::munmap(const_cast<pointer>(mapping_start()), mapping.length); // verify return value?
        }
        // If file handle is owned by this instance, close it 
        if (mapping.owner) {
            ::close(file.handle); // verify return value?
        }

        // Reset fields
        clear();
        return error::none;
    }

    // Flush data to disk
    std::error_code sync() {
        // Verify file is open
        if (not open()) {
            return std::make_error_code(std::errc::bad_file_descriptor);
        }
        // Flush data to disk
        if (data() != nullptr) {
            if (::msync(mapping_start(), mapping.length, MS_SYNC) != 0) {
                return error::last();
            }
        }

        return error::none;
    }

    // Swap
    void swap(mmap<byte_type>& other) noexcept {
        if (this == &other) { return; }

        std::swap(file.data, other.file.data);
        std::swap(file.handle, other.file.handle);
        std::swap(file.length, other.file.length);
        std::swap(mapping.length, other.mapping.length);
        std::swap(mapping.owner, other.mapping.owner);
    }

  private:
  // Implementation ///////////

    // Returns start of mapping
    pointer mapping_start() noexcept {
        return data() ? data() - offset() : nullptr;
    }

    // Clear data members
    void clear() noexcept {
        file.data = nullptr;
        file.handle = INVALID_HANDLE_VALUE;
        file.length = 0;
        mapping.length = 0;
        mapping.owner = false;
    }

  // Data /////////////////////

    struct file {
        pointer data = nullptr;                    // Points to the first requested byte, not to the actual start of the mapping
        handle_type handle = INVALID_HANDLE_VALUE; // Windows file handle
        size_type length = 0;                      // Requested length in bytes: may not be the length of the full mapping
    } file;
    struct mapping {
        size_type length = 0;                      // Length of the full mapping
        bool owner = false;                        // This flag is used to determine when to close file handle
    } mapping;
};

///////////////////////////////////////////////
// Operators

template<typename type>
bool operator==(const mmap<type>& lhs, const mmap<type>& rhs) {
    return lhs.data() == rhs.data() and lhs.length() == rhs.length();
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
    if (lhs.data() == rhs.data()) { return lhs.length() > rhs.length(); }
    return lhs.data() > rhs.data();
}

template<typename type>
bool operator>=(const mmap<type>& lhs, const mmap<type>& rhs) {
    return !(lhs < rhs);
}

}

#endif
#endif