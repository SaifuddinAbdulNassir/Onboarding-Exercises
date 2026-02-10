
find_package(PcapPlusPlus REQUIRED)
find_package(TBB REQUIRED)

# Build application code as a library
file(GLOB_RECURSE SOURCES 
    src/*.cpp
    src/exception/*.cpp
    )

add_library(steering-app
    ${SOURCES}
)

# Public headers
target_include_directories(steering-app
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(steering-app
    Common++
    Packet++
    Pcap++
    TBB::tbb
)
