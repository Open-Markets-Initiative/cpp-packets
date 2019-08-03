set(PCAP_EXAMPLE_BINARY pcap)
add_executable(${PCAP_EXAMPLE_BINARY} main.cpp)
target_link_libraries(${PCAP_EXAMPLE_BINARY} stdc++fs)