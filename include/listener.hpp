#ifndef LISTENER_HPP
#define LISTENER_HPP

#include <memory>
#include <datatype.hpp>
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>

using client = websocketpp::client<websocketpp::config::asio_tls_client>;
using client_ptr = websocketpp::lib::shared_ptr<client>;
using context = boost::asio::ssl::context;
using context_ptr = websocketpp::lib::shared_ptr<context>;

class Listener
{
private:
    client_ptr m_client;
    std::shared_ptr<book> m_book;

    static context_ptr on_tls_init();

public:
    Listener(std::shared_ptr<book> &ledger);
    void connect(const std::string &uri);
};

#endif