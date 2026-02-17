# CMake version
cmake_minimum_required(VERSION 3.13)

# Project name
project(pcap-converter)

# set C++ version
set(CMAKE_CXX_STANDARD 20)

# require C++ version
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include src folder
add_subdirectory(app)
