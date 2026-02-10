#Find packages
find_package(TBB REQUIRED)

#Find source files
file(GLOB_RECURSE TEST_SOURCES
    src/*.cpp
    )

# Add executable
add_executable(steering-tests
    ${TEST_SOURCES}
)

# Include App headers
target_include_directories(steering-tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/app/include
)

# Link everything
target_link_libraries(steering-tests
    steering-app
    Common++
    gmock
    gtest
    gtest_main
    Packet++
    Pcap++
    TBB::tbb
)

# Enable testing globally
enable_testing()

# GoogleTest / GoogleMock (FetchContent)
include(FetchContent)

# Register tests with CTest
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

