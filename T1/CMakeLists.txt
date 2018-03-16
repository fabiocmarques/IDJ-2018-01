cmake_minimum_required(VERSION 3.9)
project(T1)

set(CMAKE_CXX_STANDARD 11)

include_directories(BEFORE include)

add_executable(T1 src/main.cpp)