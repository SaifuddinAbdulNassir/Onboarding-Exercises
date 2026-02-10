
find_package(PcapPlusPlus REQUIRED)
find_package(libfort REQUIRED)
find_package(cxxopts REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(pcap-convert ${SOURCES})

target_include_directories(pcap-convert
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(pcap-convert
PRIVATE
    cxxopts::cxxopts
    libfort::fort
    pcap
    PcapPlusPlus::Common++
    PcapPlusPlus::Packet++
    PcapPlusPlus::Pcap++
)
