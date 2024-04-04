#pragma once

#include <cstdint>
#include <unordered_map>

namespace Exchange
{
enum class Server : uint8_t
{
    BinanceTestnet = 0
};

namespace Futures
{
extern const std::unordered_map<Server, const char *> RestAddresses;
}

} // namespace Exchange
