
add_executable(poster
    src/main.cpp
    src/poster.cpp
    src/requests.cpp
)

set_target_properties(
    poster PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

target_include_directories(
    poster
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include
            ${MySQLCPPConnector_INCLUDE_DIR}
)

target_link_libraries(
    poster
    PUBLIC  ${MySQLCPPConnector_LIB}
            Common
            OpenSSL::SSL
            OpenSSL::Crypto
            nlohmann_json::nlohmann_json
            CURL::libcurl
)
