add_executable(steering_tests
    src/ProtocolUtilTest.cpp
    src/SteeringTargetTest.cpp
    src/SteeringRuleTest.cpp
    src/SteeringRuntimeTest.cpp
    src/SteeringWorkerTest.cpp
)

# Include App headers
target_include_directories(steering_tests
    PRIVATE
        ${CMAKE_SOURCE_DIR}/App/include
)

# Link everything

find_package(TBB REQUIRED)

target_link_libraries(steering_tests
    steering_app
    gtest
    gmock
    gtest_main
    Packet++
    Pcap++
    Common++
    TBB::tbb
)

# Register with CTest
add_test(NAME steering_tests COMMAND steering_tests)
