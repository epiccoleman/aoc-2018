cmake_minimum_required(VERSION 3.1)

set(CMAKE_C_COMPILER "gcc-8")
set(CMAKE_CXX_COMPILER "g++-8")

project(AdventOfCode2018)

set(BOOST_VERSION "1_69_0")
set(BOOST_ROOT /usr/local/src/${BOOST_VERSION})
set(BOOST_LIBRARYDIR ${BOOST_ROOT}/stage/lib)
find_package( Boost 1.69 COMPONENTS REQUIRED)
include_directories(${Boost_INCLUDE_DIR})


file(GLOB_RECURSE srcs
    "*.cpp"
    "utils/*.cpp"
)
list(FILTER srcs EXCLUDE REGEX Test)

file(GLOB_RECURSE test_srcs
    "*Test.cpp"
    "utils/*Test.cpp"
)

add_library(AdventOfCode ${srcs})
target_include_directories(AdventOfCode PUBLIC ${Boost_INCLUDE_DIR})
target_compile_features(AdventOfCode PUBLIC cxx_std_20)

add_executable(AdventOfCodeTest ${test_srcs} testMain.cpp)
target_link_libraries(AdventOfCodeTest AdventOfCode gtest pthread)
