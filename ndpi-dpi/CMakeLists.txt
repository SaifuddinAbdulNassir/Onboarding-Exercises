cmake_minimum_required(VERSION 3.10)
project(ndpi_dpi)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "/usr/local/lib/cmake/pcapplusplus")

if(DEFINED DPDK_FOUND AND NOT TARGET DPDK::DPDK)
    unset(DPDK_FOUND CACHE)
endif()
find_package(DPDK REQUIRED)

find_package(PcapPlusPlus REQUIRED CONFIG)

include_directories(
    /usr/local/include
    /usr/local/include/ndpi
    /usr/include
    /usr/include/ndpi
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

link_directories(/usr/local/lib)

set(SOURCES
    src/AppState.cpp
    src/ConnectionInfo.cpp
    src/ConnectionKey.cpp
    src/ConnectionKeyHash.cpp
    src/main.cpp
)

add_executable(ndpi_dpi ${SOURCES})

target_link_libraries(ndpi_dpi
    ndpi
    PcapPlusPlus::Packet++
    PcapPlusPlus::Pcap++
    PcapPlusPlus::Common++
    pcap
    pthread
)
