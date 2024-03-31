file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(poster
    ${SOURCES}
    ${COMMON_SOURCE_FILES}
)

set_target_properties(poster PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3"
)

target_include_directories(poster
    PUBLIC ${COMMON_INCLUDE_DIRS}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PUBLIC ${MySQLCPPConnector_INCLUDE_DIR}
)

target_link_libraries(poster
    PUBLIC ${MySQLCPPConnector_LIB}
    PUBLIC OpenSSL::SSL
    PUBLIC OpenSSL::Crypto
    PUBLIC nlohmann_json::nlohmann_json
    PUBLIC CURL::libcurl
)
