
find_package(PcapPlusPlus REQUIRED)
find_package(libfort REQUIRED)
find_package(cxxopts REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB SOURCES "src/*.cpp")

add_executable(pcap-convert ${SOURCES})

target_link_libraries(pcap-convert
    Common++
    cxxopts::cxxopts
    libfort::fort
    Packet++
    pcap
    Pcap++
)
