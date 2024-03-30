#ifndef WEBSOCKET_HPP
#define WEBSOCKET_HPP

#include <aliases.hpp>

class Websocket
{
protected:
    client_ptr m_client;
    std::shared_ptr<book> m_book;

    static context_ptr on_tls_init();

public:
    Websocket(std::shared_ptr<book> &ledger);
    virtual void connect(const std::string &uri);
    virtual void run();
};

#endif