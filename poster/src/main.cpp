#include <chrono>
#include <cstdint>
#include <exchanges.hpp>
#include <poster.hpp>
#include <request.hpp>
#include <request_attributes_builder.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

int main()
{
    if (!spdlog::get("logger(poster)"))
    {
        spdlog::stdout_color_mt("logger(poster)");
    }
    std::shared_ptr<spdlog::logger> logger = spdlog::get("logger(poster)");
    const std::string API_KEY = "4d0ba1e12ac22a7d3739a86ffebb35d2db0d4b3c79cd44af959092f049d5709f";
    const std::string API_SECRET = "d03f6b38059b3829b172439fb1193ae02845ffed72dfa3a26488fa066628ba09";
    uint64_t timestamp =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
            .count();
    Exchange::Binance::RequestBodyAttributesBuilder request_attributes =
        Exchange::Binance::RequestBodyAttributesBuilder()
            .setSymbol("BTCUSDT")
            .setSide("BUY")
            .setType("LIMIT")
            .setTimeInForce("GTC")
            .setQuantity("0.002")
            .setPrice("66000")
            .setRecvWindow("5000")
            .setTimestamp(timestamp);

    std::string payload = Exchange::Binance::Request::create_payload(request_attributes.build());
    Components::Poster poster(API_KEY, API_SECRET);
    logger->info("payload: {}", payload);
    int response_status = poster.send(Exchange::Server::BinanceTestnet, payload);
    if (response_status == -1)
    {
        logger->critical("Failed to send request!");
        return -1;
    }
    return 0;
}