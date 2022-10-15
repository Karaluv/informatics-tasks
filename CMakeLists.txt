# CMake entry point
cmake_minimum_required(VERSION 3.0)
project(InfLabs)

include(CTest)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# comment dofferent subdirections not to built them
add_subdirectory(labs)

# add_subdirectory(temp)
