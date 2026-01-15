# Build application code as a library
add_library(steering_app
    src/exception/DropPacketException.cpp
    src/exception/DuplicatedTargetException.cpp
    src/exception/InvalidArgumentException.cpp
    src/exception/InvalidProtocolException.cpp
    src/ProtocolUtil.cpp
    src/SteeringTarget.cpp
    src/SteeringRule.cpp
    src/SteeringRuntime.cpp
    src/SteeringWorker.cpp
)

# Public headers
target_include_directories(steering_app
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
         ${CMAKE_SOURCE_DIR}/../PcapPlusPlus/Common++/header
)

# PcapPlusPlus
find_package(PcapPlusPlus REQUIRED)

target_include_directories(steering_app
    PUBLIC
        ${PCAPPLUSPLUS_INCLUDE_DIRS}
)

find_package(TBB REQUIRED)

target_link_libraries(steering_app
    PUBLIC
        ${PCAPPLUSPLUS_LIBRARIES}
)

target_link_libraries(steering_app
    Packet++
    Pcap++
    Common++
    TBB::tbb
)

