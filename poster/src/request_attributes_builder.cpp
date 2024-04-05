#include <request_attributes_builder.hpp>

namespace Exchange::Binance
{

RequestBodyAttributesBuilder &RequestBodyAttributesBuilder::setSymbol(const std::string &symbol)
{
    attrs.symbol = symbol;
    return *this;
}

RequestBodyAttributesBuilder &RequestBodyAttributesBuilder::setSide(const std::string &side)
{
    attrs.side = side;
    return *this;
}

RequestBodyAttributesBuilder &RequestBodyAttributesBuilder::setType(const std::string &type)
{
    attrs.type = type;
    return *this;
}

RequestBodyAttributesBuilder &RequestBodyAttributesBuilder::setTimeInForce(const std::string &timeInForce)
{
    attrs.timeInForce = timeInForce;
    return *this;
}

RequestBodyAttributesBuilder &RequestBodyAttributesBuilder::setQuantity(const std::string &quantity)
{
    attrs.quantity = quantity;
    return *this;
}

RequestBodyAttributesBuilder &RequestBodyAttributesBuilder::setPrice(const std::string &price)
{
    attrs.price = price;
    return *this;
}

RequestBodyAttributesBuilder &RequestBodyAttributesBuilder::setNewClientOrderId(const std::string &newClientOrderId)
{
    attrs.newClientOrderId = newClientOrderId;
    return *this;
}

RequestBodyAttributesBuilder &RequestBodyAttributesBuilder::setStopPrice(const std::string &stopPrice)
{
    attrs.stopPrice = stopPrice;
    return *this;
}

RequestBodyAttributesBuilder &RequestBodyAttributesBuilder::setIcebergQty(const std::string &icebergQty)
{
    attrs.icebergQty = icebergQty;
    return *this;
}

RequestBodyAttributesBuilder &RequestBodyAttributesBuilder::setNewOrderRespType(const std::string &newOrderRespType)
{
    attrs.newOrderRespType = newOrderRespType;
    return *this;
}

RequestBodyAttributesBuilder &RequestBodyAttributesBuilder::setRecvWindow(const std::string &recvWindow)
{
    attrs.recvWindow = recvWindow;
    return *this;
}

RequestBodyAttributesBuilder &RequestBodyAttributesBuilder::setTimestamp(uint64_t timestamp)
{
    attrs.timestamp = timestamp;
    return *this;
}

RequestBodyAttributesBuilder::RequestBodyAttributes RequestBodyAttributesBuilder::build() const
{
    return attrs;
}

} // namespace Exchange::Binance