#include <cstdint>
#include <requests.hpp>
#include <string>

namespace Exchange::Binance
{

RequestBodyAttributes::RequestBodyAttributes(const uint64_t timestamp, const std::string &symbol,
                                             const std::string &side, const std::string &type,
                                             const std::string &timeInForce, const std::string &quantity,
                                             const std::string &price, const std::string &newClientOrderId,
                                             const std::string &stopPrice, const std::string &icebergQty,
                                             const std::string &newOrderRespType, const std::string &recvWindow)
    : symbol(symbol), side(side), type(type), timeInForce(timeInForce), quantity(quantity), price(price),
      newClientOrderId(newClientOrderId), stopPrice(stopPrice), icebergQty(icebergQty),
      newOrderRespType(newOrderRespType), recvWindow(recvWindow), timestamp(timestamp)
{
}

std::string CreateRequest::payload(
    // const std::string &apiKey,
    const RequestBodyAttributes &data)
{
    std::string payload;
    // payload += "apiKey=" + apiKey + "&";
    if (!data.symbol.empty())
        payload += "symbol=" + data.symbol + "&";
    if (!data.side.empty())
        payload += "side=" + data.side + "&";
    if (!data.type.empty())
        payload += "type=" + data.type + "&";
    if (!data.timeInForce.empty())
        payload += "timeInForce=" + data.timeInForce + "&";
    if (!data.quantity.empty())
        payload += "quantity=" + data.quantity + "&";
    if (!data.price.empty())
        payload += "price=" + data.price + "&";
    if (!data.newClientOrderId.empty())
        payload += "newClientOrderId=" + data.newClientOrderId + "&";
    if (!data.stopPrice.empty())
        payload += "stopPrice=" + data.stopPrice + "&";
    if (!data.icebergQty.empty())
        payload += "icebergQty=" + data.icebergQty + "&";
    if (!data.newOrderRespType.empty())
        payload += "newOrderRespType=" + data.newOrderRespType + "&";
    if (!data.recvWindow.empty())
        payload += "recvWindow=" + data.recvWindow + "&";
    payload += "timestamp=" + std::to_string(data.timestamp);

    return payload;
}

} // namespace Exchange::Binance