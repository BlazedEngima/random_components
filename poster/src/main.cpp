#include <chrono>
#include <config.hpp>
#include <cstdint>
#include <exchanges.hpp>
#include <memory>
#include <poster.hpp>
#include <request.hpp>
#include <request_attributes_builder.hpp>
#include <request_types.hpp>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

int main(int argc, char *argv[])
{
    if (!spdlog::get("logger(poster)"))
    {
        spdlog::stdout_color_mt("logger(poster)");
    }

    if (argc != 2)
    {
        spdlog::get("logger(poster)")->error("Usage: {} <config_file_path>", argv[0]);
        return 1;
    }

    std::shared_ptr<Config::Poster::Read> info = std::make_shared<Config::Poster::Read>(argv[1]);
    std::shared_ptr<spdlog::logger> logger = spdlog::get("logger(poster)");
    const std::string API_KEY = info->API_KEY;
    const std::string API_SECRET = info->API_SECRET;

    uint64_t timestamp =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
            .count();
    Exchange::Binance::RequestBodyAttributesBuilder request_attributes =
        Exchange::Binance::RequestBodyAttributesBuilder()
            .setSymbol("BTCUSDT")
            // .setSide("")
            .setSide("BUY")
            .setType("LIMIT")
            .setTimeInForce("GTC")
            .setQuantity("0.005")
            .setPrice("73500")
            .setRecvWindow("5000")
            // .setOrderId("3772261519")
            .setTimestamp(timestamp);

    std::string payload = Exchange::Binance::Request::create_payload(request_attributes.build());
    Components::Poster poster(API_KEY, API_SECRET);
    logger->info("payload: {}", payload);
    int response_status =
        poster.send(Exchange::Server::BinanceTestnet, Exchange::HTTPRequest::RequestType::POST, payload);
    // poster.send(Exchange::Server::BinanceTestnet, Exchange::HTTPRequest::RequestType::DELETE, payload);
    if (response_status == -1)
    {
        logger->critical("Failed to send request!");
        return -1;
    }
    return 0;
}