#pragma once

#include <commons.hpp>

namespace Common
{
class Websocket
{
  public:
    Websocket();
    virtual ~Websocket() = default;
    virtual void connect(const std::string &uri);
    virtual void run();

  protected:
    static context_ptr on_tls_init();

    client_ptr m_client;
    std::unordered_map<std::string, client::connection_ptr> m_connections;
};
} // namespace Common