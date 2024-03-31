#ifndef WEBSOCKET_HPP
#define WEBSOCKET_HPP

#include <commons.hpp>

class Websocket
{
protected:
    client_ptr m_client;
    std::unordered_map<std::string, client::connection_ptr> m_connections;

    static context_ptr on_tls_init();

public:
    Websocket();
    virtual void connect(const std::string &uri);
    virtual void run();
};

#endif