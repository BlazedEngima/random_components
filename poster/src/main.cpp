#include <poster.hpp>
#include <chrono>
#include <thread>

#define API_KEY "RNKIQyoT6BWMWCmTj5CBdYcTMKr0HsuFr3ifRWyPJAN1aEslMbRnGnzsx5WwCIfZ"
#define API_SECRET "raa0KHumoX1fbdGfs0MC70PENfGv3K9hTeGULw2JvAxK3zC4jSHUtSXOk8fDS5LX"

int main()
{
    Poster poster(API_KEY, API_SECRET);

    poster.connect("wss://testnet.binance.vision/ws-api/v3");
    
    std::thread poster_thread([&poster]() {
        poster.run();
    });

    std::this_thread::sleep_for(std::chrono::seconds(1));

    poster.send(
        "1",
        "BTCUSDT",
        "BUY",
        "LIMIT",
        "GTC",
        "0.001",
        "70000",
        "wss://testnet.binance.vision/ws-api/v3");

    std::cout << "Order placed" << std::endl;

    poster_thread.join();

    return 0;
}