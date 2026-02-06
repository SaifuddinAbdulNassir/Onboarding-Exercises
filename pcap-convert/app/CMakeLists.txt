
find_package(PcapPlusPlus REQUIRED)
find_package(libfort REQUIRED)
find_package(cxxopts REQUIRED)

file(GLOB SOURCES "src/*.cpp")

add_executable(pcap-convert ${SOURCES})

target_include_directories(pcap-convert
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(pcap-convert
    Common++
    cxxopts::cxxopts
    libfort::fort
    Packet++
    pcap
    Pcap++
)
