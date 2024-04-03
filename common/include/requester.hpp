#pragma once

#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace Common
{
class Requester
{
  public:
    static std::vector<std::string> get_top_assets(const int limit = 50);

  private:
    static size_t write_callback(void *contents, size_t size, size_t nmemb, std::string *response);
};

} // namespace Common