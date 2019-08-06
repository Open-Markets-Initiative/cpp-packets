#include "catch.hpp"

#include <array>

#include <omi/packet/ipv4/header.hpp>

template<typename... value>
std::array<std::byte, sizeof...(value)> bytes(value&& ... args) noexcept {
    return { std::byte(std::forward<value>(args))... };
}

TEST_CASE("Verify ipv4 header value", "[ipv4]") {
    // actual ipv4 header
    auto buffer = bytes(
        0x45, 0x00, 0x05, 0x7c, 0x00, 0x00, 0x40, 0x00, 
        0x38, 0x11, 0x92, 0x1e, 0xcd, 0xd1, 0xde, 0x55, 
        0xe0, 0x00, 0x1f, 0x2b);

    auto ipv4 = omi::ipv4::header::parse(buffer.data());

    auto actual = ipv4->length.get();
    auto expected = 1404;

    REQUIRE(expected == actual);
}

TEST_CASE("Verify ipv4 has version", "[ipv4]") {

    auto buffer = bytes(
        0x45, 0x00, 0x05, 0x7c, 0x00, 0x00, 0x40, 0x00, 
        0x38, 0x11, 0x92, 0x1e, 0xcd, 0xd1, 0xde, 0x55, 
        0xe0, 0x00, 0x1f, 0x2b);

    auto ipv4 = omi::ipv4::header::parse(buffer.data());

    REQUIRE(ipv4->info.version());
}

TEST_CASE("Verify ipv4 packet is valid", "[ipv4]") {

    auto buffer = bytes(
        0x45, 0x00, 0x05, 0x7c, 0x00, 0x00, 0x40, 0x00, 
        0x38, 0x11, 0x92, 0x1e, 0xcd, 0xd1, 0xde, 0x55, 
        0xe0, 0x00, 0x1f, 0x2b);

    auto ipv4 = omi::ipv4::header::parse(buffer.data());
    
    auto actual = ipv4->valid();
    auto expected = true;

    REQUIRE(expected == actual);
}
