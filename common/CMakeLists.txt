add_library(
    Common 
    SHARED  src/encrypt.cpp
            src/websocket.cpp
            src/jobs.cpp
            src/exchanges.cpp)

target_include_directories(
    Common PUBLIC include
)

target_link_libraries(
    Common
    PUBLIC  nlohmann_json::nlohmann_json
            OpenSSL::SSL
            OpenSSL::Crypto
)