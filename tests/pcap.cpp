#include "catch.hpp"

#include <array>

#include <omi/packet/pcap/header.hpp>
#include <omi/packet/pcap/frame.hpp>

template<typename... value>
std::array<std::byte, sizeof...(value)> bytes(value&& ... args) noexcept {
    return {std::byte(std::forward<value>(args))...};
}

TEST_CASE("Verify pcap header value", "[pcap file]") {
    // Actual pcap file header
    auto buffer = bytes(
        0xd4, 0xc3, 0xb2, 0xa1, 0x02, 0x20, 0x04, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
        0x20, 0x20, 0x04, 0x20, 0x01, 0x20, 0x20, 0x20);

    auto pcap = omi::pcap::header::parse(buffer.data());

    REQUIRE(pcap->valid());
}

TEST_CASE("Verify pcap frame value", "[pcap frame]") {
    // actual pcap frame header
    auto buffer = bytes(
        0xd1, 0x90, 0x4c, 0x20, 0xc3, 0x7a, 0x20, 0x20,
        0x8e, 0x05, 0x20, 0x20);

    auto frame = omi::pcap::frame::parse(buffer.data());

    REQUIRE(frame->valid());
}