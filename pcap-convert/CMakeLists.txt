cmake_minimum_required(VERSION 3.10)
project(pcap-convert)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(/usr/local/include/pcapplusplus
${CMAKE_CURRENT_SOURCE_DIR}/include
)
link_directories(/usr/local/lib)

file(GLOB SOURCES "src/*.cpp")

add_executable(pcap-convert ${SOURCES})

target_link_libraries(pcap-convert
    Common++
    Packet++
    pcap
    Pcap++
)
