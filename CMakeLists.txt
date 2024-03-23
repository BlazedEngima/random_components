cmake_minimum_required(VERSION 3.22)

set(CXX_STANDARD_REQUIRED 20)

project(listener)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

find_package(OpenSSL REQUIRED)
find_package(MySQLCPPConnector REQUIRED)
include(cmake/fetchers/NlohmannJSON.cmake)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(listener ${SOURCES})
target_include_directories(listener 
    PUBLIC "${CMAKE_SOURCE_DIR}/include"
    PUBLIC ${MySQLCPPConnector_INCLUDE_DIR}
)
target_link_libraries(listener 
    PUBLIC ${MySQLCPPConnector_LIB}
    PUBLIC OpenSSL::SSL
    PUBLIC OpenSSL::Crypto
    PUBLIC nlohmann_json::nlohmann_json
)
