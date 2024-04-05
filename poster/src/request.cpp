#include <request.hpp>

namespace Exchange::Binance
{

std::string Request::create_payload(const RequestBodyAttributesBuilder::RequestBodyAttributes &data)
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