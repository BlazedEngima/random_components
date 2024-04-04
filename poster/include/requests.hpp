#pragma once

#include <cstdint>
#include <nlohmann/json.hpp>
#include <string>

namespace Exchange::Binance
{
struct RequestBodyAttributes
{
    std::string symbol;
    std::string side;
    std::string type;
    std::string timeInForce;
    std::string quantity;
    std::string price;
    std::string newClientOrderId;
    std::string stopPrice;
    std::string icebergQty;
    std::string newOrderRespType;
    std::string recvWindow;
    uint64_t timestamp;

    RequestBodyAttributes(const uint64_t timestamp, const std::string &symbol = "", const std::string &side = "",
                          const std::string &type = "", const std::string &timeInForce = "",
                          const std::string &quantity = "", const std::string &price = "",
                          const std::string &newClientOrderId = "", const std::string &stopPrice = "",
                          const std::string &icebergQty = "", const std::string &newOrderRespType = "",
                          const std::string &recvWindow = "");
};

class CreateRequest
{
  public:
    static std::string payload(const RequestBodyAttributes &specs);
};
} // namespace Exchange::Binance