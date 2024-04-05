#include <curl/curl.h>
#include <curl/easy.h>
#include <encrypt.hpp>
#include <nlohmann/json.hpp>
#include <poster.hpp>

namespace Components
{

size_t Poster::write_callback(void *contents, size_t size, size_t nmemb, std::string *s)
{
    size_t write_size = size * nmemb;
    s->append((char *)contents, write_size);
    return write_size;
}

int Poster::send(Exchange::Server server, std::string &payload)
{
    std::string signature = Common::EncryptProtocol::HMAC_SHA256::sign(secret, payload);
    payload += "&signature=" + signature;
    CURL *curl = curl_easy_init();

    if (!curl)
    {
        logger->error("failed to initialize curl");
        return -1;
    }

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, request_header);

    curl_easy_setopt(curl, CURLOPT_URL, Exchange::Futures::RestAddresses.at(server));
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());

    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);

    // free resources
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);

    if (res != CURLE_OK)
    {
        logger->error("failed to perform curl request: {}", curl_easy_strerror(res));
        return -1;
    }

    // maybe we should check the response status code
    nlohmann::json response_json = nlohmann::json::parse(response);
    logger->info("response: {}", response_json.dump(4));

    return 0;
}

Poster::Poster(const API_KEY &key, const API_SECRET &secret) : key(key), secret(secret)
{
    header_line = "X-MBX-APIKEY: " + key;
    request_header = header_line.c_str();
    if (!spdlog::get("logger(poster)"))
    {
        spdlog::stdout_color_mt("logger(poster)");
    }
    logger = spdlog::get("logger(poster)");
}

} // namespace Components