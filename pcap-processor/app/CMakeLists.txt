# Find packages
find_package(cxxopts REQUIRED)
find_package(libfort REQUIRED)
find_package(PcapPlusPlus REQUIRED)

# Find source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# Add pcap-processor
add_executable(pcap-processor ${SOURCES})

# Add include directories
target_include_directories(pcap-processor
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link to libraries
target_link_libraries(pcap-processor
  PRIVATE
    cxxopts::cxxopts
    libfort::fort
    pcap
    PcapPlusPlus::Common++
    PcapPlusPlus::Packet++
    PcapPlusPlus::Pcap++
)
