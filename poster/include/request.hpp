#pragma once

#include <nlohmann/json.hpp>
#include <request_attributes_builder.hpp>
#include <string>

namespace Exchange::Binance
{

class Request
{
  public:
    static std::string create_payload(const RequestBodyAttributesBuilder::RequestBodyAttributes &specs);
};

} // namespace Exchange::Binance