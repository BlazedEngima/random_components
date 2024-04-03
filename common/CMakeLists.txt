add_library(Common SHARED)

target_sources(
    Common
    PUBLIC  src/requester.cpp
            src/websocket.cpp
            src/jobs.cpp
)

target_include_directories(
    Common PUBLIC include
)

target_link_libraries(
    Common
    PUBLIC  nlohmann_json::nlohmann_json
)