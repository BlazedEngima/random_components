#include <chrono>
#include <cstdint>
#include <exchanges.hpp>
#include <poster.hpp>
#include <requests.hpp>

int main()
{
    const std::string API_KEY = "4d0ba1e12ac22a7d3739a86ffebb35d2db0d4b3c79cd44af959092f049d5709f";
    const std::string API_SECRET = "d03f6b38059b3829b172439fb1193ae02845ffed72dfa3a26488fa066628ba09";
    uint64_t timestamp =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
            .count();
    Exchange::Binance::RequestBodyAttributes data(timestamp, "BTCUSDT", "BUY", "LIMIT", "GTC", "0.002", "65000", "", "",
                                                  "", "", "5000");
    std::string payload = Exchange::Binance::CreateRequest::payload(data);
    Poster poster(API_KEY, API_SECRET);
    poster.send(Exchange::Server::BinanceTestnet, payload);
    return 0;
}