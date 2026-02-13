
find_package(PcapPlusPlus REQUIRED)
find_package(libfort REQUIRED)
find_package(cxxopts REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(pcap-converter ${SOURCES})

target_include_directories(pcap-converter
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(pcap-converter
PRIVATE
    cxxopts::cxxopts
    libfort::fort
    pcap
    PcapPlusPlus::Common++
    PcapPlusPlus::Packet++
    PcapPlusPlus::Pcap++
)
