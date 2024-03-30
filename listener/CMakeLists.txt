file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(listener 
    ${SOURCES}
    ${COMMON_SOURCE_FILES}
)

set_target_properties(listener PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

target_include_directories(listener 
    PUBLIC ${COMMON_INCLUDE_DIRS}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PUBLIC ${MySQLCPPConnector_INCLUDE_DIR}
)

target_link_libraries(listener 
    PUBLIC ${MySQLCPPConnector_LIB}
    PUBLIC OpenSSL::SSL
    PUBLIC OpenSSL::Crypto
    PUBLIC nlohmann_json::nlohmann_json
    PUBLIC CURL::libcurl
)
