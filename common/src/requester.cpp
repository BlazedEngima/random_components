#include <iostream>
#include <requester.hpp>

namespace Common
{
size_t Requester::write_callback(void *contents, size_t size, size_t nmemb, std::string *response)
{
    size_t real_size = size * nmemb;
    response->append((char *)contents, real_size);
    return real_size;
}

std::vector<std::string> Requester::get_top_assets(const int limit)
{
    CURL *curl = curl_easy_init();
    if (!curl)
    {
        std::cerr << "Failed to initialize curl" << std::endl;
        return {};
    }

    std::string response;
    curl_easy_setopt(curl, CURLOPT_URL, "https://fapi.binance.com/fapi/v1/ticker/24hr");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK)
    {
        std::cerr << "Failed to get exchange info: " << curl_easy_strerror(res) << std::endl;
        return {};
    }

    nlohmann::json exchange_info = nlohmann::json::parse(response);
    std::sort(exchange_info.begin(), exchange_info.end(), [](const nlohmann::json &a, const nlohmann::json &b) {
        return std::stod(a["quoteVolume"].get<std::string>()) > std::stod(b["quoteVolume"].get<std::string>());
    });

    std::vector<std::string> symbols;
    int end = std::min(limit, (int)exchange_info.size());
    for (int i = 0; i < end; i++)
    {
        std::string symbol = exchange_info[i]["symbol"].get<std::string>();
        std::transform(symbol.begin(), symbol.end(), symbol.begin(), ::tolower);
        symbols.push_back(symbol);
    }

    return symbols;
}
} // namespace Common