#pragma once

#include <commons.hpp>
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

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
    std::shared_ptr<spdlog::logger> logger;
};

} // namespace Common