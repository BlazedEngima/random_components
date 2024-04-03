#pragma once

#include <datatype.hpp>
#include <nlohmann/json.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_client.hpp>

namespace Common
{

using book = std::unordered_map<std::string, DataType::Record>;
using client = websocketpp::client<websocketpp::config::asio_tls_client>;
using client_ptr = websocketpp::lib::shared_ptr<client>;
using context = boost::asio::ssl::context;
using context_ptr = websocketpp::lib::shared_ptr<context>;

} // namespace Common