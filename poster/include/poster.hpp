#pragma once

#include <cstddef>
#include <exchanges.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <string>

namespace Components
{

class Poster
{
    using API_KEY = std::string;
    using API_SECRET = std::string;
    using HEADER = std::string;
    using REQUEST_HEADER = const char *;

  public:
    int send(Exchange::Server server, std::string &payload);

    Poster(const API_KEY &key, const API_SECRET &secret);

  protected:
    std::shared_ptr<spdlog::logger> logger;

  private:
    static size_t write_callback(void *contents, size_t size, size_t nmemb, std::string *s);

    API_KEY key;
    API_SECRET secret;
    HEADER header_line;
    REQUEST_HEADER request_header;
};

} // namespace Components