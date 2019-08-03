# c++ packets regression tests
add_executable(tests main.cpp
  mapped.cpp
  ethernet.cpp
  ipv4.cpp
  pcap.cpp
)
add_test(NAME tests COMMAND tests)
