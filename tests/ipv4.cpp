#include "catch.hpp"

#include <omi/packet/byte/array.hpp>
#include <omi/packet/ipv4/header.hpp>

TEST_CASE("Verify ipv4 packet length", "[ipv4]") {

    auto buffer = omi::bytes(
        0x45, 0x00, 0x05, 0x7c, 0x00, 0x00, 0x40, 0x00, 
        0x38, 0x11, 0x92, 0x1e, 0xcd, 0xd1, 0xde, 0x55, 
        0xe0, 0x00, 0x1f, 0x2b);

    auto ipv4 = omi::ipv4::header::parse(buffer.data());

    auto expected = 1404;
    auto actual = ipv4->length.get();

    REQUIRE(expected == actual);
}

TEST_CASE("Verify ipv4 version", "[ipv4]") {

    auto buffer = omi::bytes(
        0x45, 0x00, 0x05, 0x7c, 0x00, 0x00, 0x40, 0x00, 
        0x38, 0x11, 0x92, 0x1e, 0xcd, 0xd1, 0xde, 0x55, 
        0xe0, 0x00, 0x1f, 0x2b);

    auto ipv4 = omi::ipv4::header::parse(buffer.data());

    auto expected = 4;
    auto actual = ipv4->info.version();

    REQUIRE(expected == actual);
}

TEST_CASE("Verify ipv4 header length", "[ipv4]") {

    auto buffer = omi::bytes(
        0x45, 0x00, 0x05, 0x7c, 0x00, 0x00, 0x40, 0x00,
        0x38, 0x11, 0x92, 0x1e, 0xcd, 0xd1, 0xde, 0x55,
        0xe0, 0x00, 0x1f, 0x2b);

    auto ipv4 = omi::ipv4::header::parse(buffer.data());

    auto expected = 20;
    auto actual = ipv4->info.header();

    REQUIRE(expected == actual);
}

TEST_CASE("Verify ipv4 packet is valid", "[ipv4]") {

    auto buffer = omi::bytes(
        0x45, 0x00, 0x05, 0x7c, 0x00, 0x00, 0x40, 0x00, 
        0x38, 0x11, 0x92, 0x1e, 0xcd, 0xd1, 0xde, 0x55, 
        0xe0, 0x00, 0x1f, 0x2b);

    auto ipv4 = omi::ipv4::header::parse(buffer.data());

    auto condition = ipv4->valid();

    REQUIRE(condition);
}