#ifndef COMMONS_HPP
#define COMMONS_HPP

#include <memory>
#include <datatype.hpp>
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>
#include <nlohmann/json.hpp>

using book = std::unordered_map<std::string, DataType::Record>;
using client = websocketpp::client<websocketpp::config::asio_tls_client>;
using client_ptr = websocketpp::lib::shared_ptr<client>;
using context = boost::asio::ssl::context;
using context_ptr = websocketpp::lib::shared_ptr<context>;

#endif