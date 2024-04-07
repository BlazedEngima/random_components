#pragma once

#include <cstdint>
#include <string>

namespace Exchange::Binance
{
class RequestBodyAttributesBuilder
{
  public:
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

        std::string origClientOrderId;
        std::string orderId;
        std::string cancelRestrictions;

        uint64_t timestamp;
    };

    RequestBodyAttributesBuilder &setSymbol(const std::string &symbol);
    RequestBodyAttributesBuilder &setSide(const std::string &side);
    RequestBodyAttributesBuilder &setType(const std::string &type);
    RequestBodyAttributesBuilder &setTimeInForce(const std::string &timeInForce);
    RequestBodyAttributesBuilder &setQuantity(const std::string &quantity);
    RequestBodyAttributesBuilder &setPrice(const std::string &price);
    RequestBodyAttributesBuilder &setNewClientOrderId(const std::string &newClientOrderId);
    RequestBodyAttributesBuilder &setStopPrice(const std::string &stopPrice);
    RequestBodyAttributesBuilder &setIcebergQty(const std::string &icebergQty);
    RequestBodyAttributesBuilder &setNewOrderRespType(const std::string &newOrderRespType);
    RequestBodyAttributesBuilder &setRecvWindow(const std::string &recvWindow);
    RequestBodyAttributesBuilder &setTimestamp(uint64_t timestamp);
    RequestBodyAttributesBuilder &setOrigClientOrderId(const std::string &origClientOrderId);
    RequestBodyAttributesBuilder &setOrderId(const std::string &orderId);
    RequestBodyAttributesBuilder &setCancelRestrictions(const std::string &cancelRestrictions);

    RequestBodyAttributes build() const;

  private:
    RequestBodyAttributes attrs;
};

} // namespace Exchange::Binance