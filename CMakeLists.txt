cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

project(cpp_components)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

find_package(OpenSSL REQUIRED)
find_package(MySQLCPPConnector REQUIRED)
find_package(CURL REQUIRED COMPONENTS HTTP HTTPS) 
include(cmake/fetchers/NlohmannJSON.cmake)

set(COMMON_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/common/include")
file(GLOB_RECURSE COMMON_SOURCE_FILES "${CMAKE_SOURCE_DIR}/common/src/*.cpp")

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/listener)
    add_subdirectory(listener)
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/poster)
    add_subdirectory(poster)
endif()