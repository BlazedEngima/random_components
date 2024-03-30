#ifndef WEBSOCKET_HPP
#define WEBSOCKET_HPP

#include <aliases.hpp>
#include <msg_handler.hpp>

class Websocket
{
private:
    client_ptr m_client;
    std::shared_ptr<book> m_book;

    static context_ptr on_tls_init();

public:
    Websocket(std::shared_ptr<book> &ledger);
    void connect(const std::string &uri);
    void run();
};

#endif