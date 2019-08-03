#ifndef OMI_MAPPED_FILE_BASIC_
#define OMI_MAPPED_FILE_BASIC_

#include <iterator>

#ifdef _WIN32
# ifndef WIN32_LEAN_AND_MEAN
#  define WIN32_LEAN_AND_MEAN
# endif
# include <omi/mapped/file/windows.hpp>
#else
# include <omi/mapped/file/linux.hpp>
#endif 

namespace omi::mapped::file {

template<mode access, typename type>
struct basic {
    static_assert(is::valid(access), "Invalid access mode");

  // Traits ///////////////////

    using implementation = mmap<type>;
    using value_type = typename implementation::value_type;
    using size_type = typename implementation::size_type;
    using handle_type = typename implementation::handle_type;

    using reference = typename implementation::reference;
    using const_reference = typename implementation::const_reference;
    using pointer = typename implementation::pointer;
    using const_pointer = typename implementation::const_pointer;
    using difference_type = std::ptrdiff_t;

    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using iterator_category = std::random_access_iterator_tag;

  // Construction /////////////

    // Default constructor...any operation that attempts to access non-existent underlying data will result in undefined behaviour
    basic() = default;

    // Construct from path
    template<typename path_type>
    explicit basic(const path_type& path)
      : basic{path, 0, entire_file } {}

    // Construct from path/offset/length
    template<typename path_type>
    basic(const path_type& path, const size_type offset, const size_type length) {
        auto error = map(path, offset, length);
        if (error) {
            throw std::system_error(error);
        } 
    }

    // Construct from handle/offset/length
    basic(const handle_type handle, const size_type offset, const size_type length) {
        auto error = map(handle, offset, length);
        if (error) {
            throw std::system_error(error);
        }
    }

    // Move constructor and assignment
    basic(basic&&) = default;
    basic& operator=(basic&&) = default;

    // Destructor
    ~basic() = default;

  // Methods //////////////////

    // Map file by path
    template<typename path_type>
    std::error_code map(const path_type& path, const size_type offset, const size_type length) {
        return mapping.map(path, offset, length, access);
    }

    // Map file by handle
    std::error_code map(const handle_type handle, const size_type offset, const size_type length) {
        return mapping.map(handle, offset, length, access);
    }

    // Unmap the memory region and disassociate this instance from the underlying file
    std::error_code unmap() {
        return mapping.unmap();
    }

    // Flushes memory mapped page to disk
    template<typename = enable_if_writable<access>>
    std::error_code sync() {
        return mapping.sync();
    }

    // Standard swap
    void swap(basic& other) noexcept {
        mapping.swap(other.mapping);
    }

  // Properties ///////////////

    // Get file handle
    handle_type file_handle() const noexcept {
        return mapping.file_handle();
    }

    // Get mapping handle
    handle_type mapping_handle() const noexcept {
        return mapping.mapping_handle();
    }

    // Has a valid memory mapping been created?
    bool open() const noexcept {
        return mapping.open();
    }

    // Is mapping empty (length == 0)
    bool empty() const noexcept {
        return mapping.empty();
    }

    // Return the logical length, i.e. the number of mapped bytes
    size_type size() const noexcept {
        return mapping.length();
    }

    // Return the logical length, i.e. the number of mapped bytes
    size_type length() const noexcept {
        return mapping.length();
    }

    // Returns the actual number of bytes that are mapped, a multiple of the operating system's page allocation granularity
    size_type mapped_length() const noexcept {
        return mapping.mapped_length();
    }

    // Returns the mapping offset relative to file start 
    size_type offset() const noexcept {
        return mapping.offset();
    }

    // Returns a pointer to the first requested byte or `nullptr`
    template<typename = enable_if_writable<access>>
    pointer data() noexcept {
        return mapping.data();
    }

    // Returns a const pointer to the first requested byte or `nullptr`
    const_pointer data() const noexcept {
        return mapping.data();
    }

  // Iterators ////////////////

    // Returns an iterator to the first requested byte or end()
    template<typename = enable_if_writable<access>>
    iterator begin() noexcept {
        return data();
    }

    // Returns an iterator to the first requested byte or end()
    const_iterator cbegin() noexcept {
        return data();
    }

    // Returns an iterator after the last requested byte
    template<typename = enable_if_writable<access>>
    iterator end() noexcept {
        return begin() + length();
    }

    // Returns an iterator after the last requested byte
    const_iterator cend() noexcept {
        return cbegin() + length();
    }

    template<typename = enable_if_writable<access>>
    reverse_iterator rbegin() noexcept {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const noexcept {
        return const_reverse_iterator(end());
    }

    const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator(end());
    }

    template<typename = enable_if_writable<access>>
    reverse_iterator rend() noexcept {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const noexcept {
        return const_reverse_iterator(begin());
    }

    const_reverse_iterator crend() const noexcept {
        return const_reverse_iterator(begin());
    }

  // Operators ////////////////
    
    // Equality operator 
    friend bool operator==(const basic& lhs, const basic& rhs) {
        return lhs.mapping == rhs.mapping;
    }

    // Inequality operator 
    friend bool operator!=(const basic& lhs, const basic& rhs) {
        return !(lhs == rhs);
    }

    // Less than operator 
    friend bool operator<(const basic& lhs, const basic& rhs) {
        return lhs.mapping < rhs.mapping;
    }

    // Compound less than operator 
    friend bool operator<=(const basic& lhs, const basic& rhs) {
        return lhs.mapping <= rhs.mapping;
    }

    // Greater than operator 
    friend bool operator>(const basic& lhs, const basic& rhs) {
        return lhs.mapping > rhs.mapping;
    }

    // Compound greater than operator 
    friend bool operator>=(const basic& lhs, const basic& rhs) {
        return lhs.mapping >= rhs.mapping;
    }

    // Returns a reference to the index from the first byte, only valid for valid maps
    reference operator[](const size_type index) noexcept {
        return mapping[index];
    }

    // Returns a reference to the index from the first byte, only valid for valid maps
    const_reference operator[](const size_type index) const noexcept {
        return mapping[index];
    }

  private:

    // Operating system dependent memory file mapping
    implementation mapping;
};

}

#endif