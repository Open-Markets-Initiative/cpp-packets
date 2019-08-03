#include "catch.hpp"

#include <array>

#include <omi/packet/ethernet/header.hpp>

template<typename... value>
std::array<std::byte, sizeof...(value)> bytes(value&& ... args) noexcept {
    return { std::byte(std::forward<value>(args))... };
}

TEST_CASE("Verify ethernet info value", "[ethernet]" ) {
    // wireshark packet
    auto buffer = bytes(
        0x01, 0x00, 0x5e, 0x00, 0x1f, 0x2b, 0x00, 0x1c, 0x73, 0x05, 0x5a, 0xb2, 0x81, 0x00);

    auto ethernet = omi::ethernet::header::parse(buffer.data());

    auto actual = ethernet->info;
    auto expected = omi::ethernet::info{129};

    REQUIRE(expected == actual);
}

TEST_CASE("Verify ethernet has vlan", "[ethernet]") {
    // wireshark packet
    auto buffer = bytes(
        0x01, 0x00, 0x5e, 0x00, 0x1f, 0x2b, 0x00, 0x1c, 0x73, 0x05, 0x5a, 0xb2, 0x81, 0x00);

    auto ethernet = omi::ethernet::header::parse(buffer.data());

    REQUIRE(ethernet->info.vlan());
}
