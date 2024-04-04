#include <exchanges.hpp>

namespace Exchange::Futures
{
const std::unordered_map<Server, const char *> RestAddresses = {
    {Server::BinanceTestnet, "https://testnet.binancefuture.com/fapi/v1/order"}};
}