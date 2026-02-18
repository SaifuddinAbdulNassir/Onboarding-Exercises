cmake_minimum_required(VERSION 3.13)
project(ndpi-processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(cxxopts REQUIRED)
find_package(libfort REQUIRED)
find_package(PcapPlusPlus REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(ndpi-processor ${SOURCES})

target_include_directories(ndpi-processor PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(ndpi-processor
    cxxopts::cxxopts
    libfort::fort
    ndpi
    pcap
    PcapPlusPlus::Common++
    PcapPlusPlus::Packet++
    PcapPlusPlus::Pcap++
    pthread
)
