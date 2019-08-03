#include "catch.hpp"

#include <fstream>

#include <omi/mapped/file.hpp>

TEST_CASE( "Memory map readonly file constructor", "[memory map file]" ) {
    auto path = "readonly.txt";

    // write standard file
    std::ofstream original(path);
      original << path << std::endl;
    original.close();

    // open as mapped file
    omi::mapped::file::readonly file{path};

    auto expected = path[0];
    auto actual = static_cast<char>(file[0]);

    REQUIRE(expected == actual);
}


TEST_CASE("Memory map readwrite file constructor", "[memory map file]") {
    auto path = "readwrite.txt";

    // write standard file
    std::ofstream original(path);
      original << path << std::endl;
    original.close();

    // open as mapped file
    omi::mapped::file::readwrite file{ path };

    auto expected = path[0];
    auto actual = static_cast<char>(file[0]);

    REQUIRE(expected == actual);
}
