#include "catch.hpp"

#include <omi/packet/byte/array.hpp>
#include <omi/packet/ethernet/header.hpp>

TEST_CASE("Verify ethernet info value", "[ethernet]" ) {

    auto buffer = omi::bytes(
        0x01, 0x00, 0x5e, 0x00, 0x1f, 0x2b, 0x00, 0x1c, 0x73, 0x05, 0x5a, 0xb2, 0x81, 0x00);

    auto ethernet = omi::ethernet::header::parse(buffer.data());

    auto expected = omi::ethernet::info{ 129 };
    auto actual = ethernet->info;

    REQUIRE(expected == actual);
}

TEST_CASE("Verify ethernet has vlan", "[ethernet]") {

    auto buffer = omi::bytes(
        0x01, 0x00, 0x5e, 0x00, 0x1f, 0x2b, 0x00, 0x1c, 0x73, 0x05, 0x5a, 0xb2, 0x81, 0x00);

    auto ethernet = omi::ethernet::header::parse(buffer.data());

    auto condition = ethernet->info.vlan();

    REQUIRE(condition);
}
