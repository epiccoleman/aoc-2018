cmake_minimum_required(VERSION 3.1)

set(CMAKE_C_COMPILER "gcc-8")
set(CMAKE_CXX_COMPILER "g++-8")

project(AdventOfCode2018)

file(GLOB_RECURSE srcs
    "*.cpp"
    "utils/*.cpp"
)
list(FILTER srcs EXCLUDE REGEX Test)

file(GLOB_RECURSE test_srcs
    "*Test.cpp"
)

add_library(AdventOfCode ${srcs})
target_compile_features(AdventOfCode PUBLIC cxx_std_20)

add_executable(AdventOfCodeTest ${test_srcs} testMain.cpp)
target_link_libraries(AdventOfCodeTest AdventOfCode gtest pthread)
