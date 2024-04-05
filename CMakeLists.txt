cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(
    CMAKE_CXX_FLAGS 
    "${CMAKE_CXX_FLAGS}                 \
     -O3                                \
     -Wall                              \
     -Wextra                            \
     -Wpedantic                         \
     -Werror                            \
     -fsanitize=address                 \
    "
)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(cpp_components)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

find_package(OpenSSL REQUIRED)
find_package(MySQLCPPConnector REQUIRED)
find_package(CURL REQUIRED COMPONENTS HTTP HTTPS)
find_package(spdlog REQUIRED)
include(cmake/fetchers/NlohmannJSON.cmake)

add_subdirectory(common)

set(COMPONENTS
    listener
    poster
)

foreach(COMPONENT IN LISTS COMPONENTS)
    if(IS_DIRECTORY ${COMPONENT})
        add_subdirectory(${COMPONENT}) 
    endif()
endforeach()