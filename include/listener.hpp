#ifndef LISTENER_HPP
#define LISTENER_HPP

#include <commons.hpp>
#include <msg_handler.hpp>

class Listener
{
private:
    client_ptr m_client;
    std::shared_ptr<book> m_book;

    static context_ptr on_tls_init();

public:
    Listener(std::shared_ptr<book> &ledger);
    void connect(const std::string &uri);
    void run();
};

#endif