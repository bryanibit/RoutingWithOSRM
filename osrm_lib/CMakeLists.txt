cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -march=native -O3 -pthread")
project(Routing)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(bitness 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(bitness 64)
    message(STATUS "Building on a 64 bit system")
else()
    message(STATUS "Building on a 32 bit system")
endif()

find_package(LibOSRM REQUIRED)
link_directories(${LibOSRM_LIBRARY_DIRS})
include_directories(SYSTEM ${LibOSRM_INCLUDE_DIRS})

find_package(Boost REQUIRED COMPONENTS thread system date_time)
include_directories(${Boost_INCLUDE_DIRS})

add_library(${PROJECT_NAME} STATIC routing.cpp)
target_link_libraries(${PROJECT_NAME} ${LibOSRM_LIBRARIES} ${LibOSRM_DEPENDENT_LIBRARIES} ${Boost_LIBRARIES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LibOSRM_CXXFLAGS}" CACHE INTERNAL "cxx-flag" FORCE)
set(RouteLib "${PROJECT_NAME}" CACHE INTERNAL "osrmlib" FORCE)
set(RouteInclude "${PROJECT_SOURCE_DIR}" CACHE INTERNAL "osrmlib" FORCE)
