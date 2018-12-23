cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -march=native -O3 -pthread")
project(Plan_example)
add_subdirectory(osrm_lib)
# Add OSRM lib installed location
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/osrm_lib")
# Add routing.hpp location
include_directories("/usr/local/include/osrm")

add_executable(Plan_example main.cpp)
target_link_libraries(Plan_example ${RouteLib} )
