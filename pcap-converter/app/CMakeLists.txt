# Find packages
find_package(cxxopts REQUIRED)
find_package(libfort REQUIRED)
find_package(PcapPlusPlus REQUIRED)

# Find source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# Add pcap-converter
add_executable(pcap-converter ${SOURCES})

# Add include directories
target_include_directories(pcap-converter
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link to libraries
target_link_libraries(pcap-converter
  PRIVATE
    cxxopts::cxxopts
    libfort::fort
    pcap
    PcapPlusPlus::Common++
    PcapPlusPlus::Packet++
    PcapPlusPlus::Pcap++
)
