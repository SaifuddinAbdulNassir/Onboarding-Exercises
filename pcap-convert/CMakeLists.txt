cmake_minimum_required(VERSION 3.10)
project(pcap_convert)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(/usr/local/include/pcapplusplus
${CMAKE_CURRENT_SOURCE_DIR}/include
)
link_directories(/usr/local/lib)

add_executable(pcap-convert src/main.cpp)

target_link_libraries(pcap-convert
    Pcap++
    Packet++
    Common++
    pcap
)
