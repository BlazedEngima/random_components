
add_executable(listener
    src/main.cpp
    src/db_handler.cpp
)

set_target_properties(
    listener PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

target_include_directories(
    listener 
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include
            ${MySQLCPPConnector_INCLUDE_DIR}
)

target_link_libraries(
    listener 
    PUBLIC  ${MySQLCPPConnector_LIB}
            Common
            OpenSSL::SSL
            OpenSSL::Crypto
            nlohmann_json::nlohmann_json
            CURL::libcurl
)
