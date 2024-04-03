#pragma once

#include <commons.hpp>

class Websocket {
protected:
    client_ptr m_client;
    std::unordered_map<std::string, client::connection_ptr> m_connections;

    static context_ptr on_tls_init();

public:
    Websocket();
    virtual ~Websocket() = default;
    virtual void connect(const std::string& uri);
    virtual void run();
};