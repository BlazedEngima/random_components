#include <memory>
#include <websocket.hpp>

namespace Common
{

Websocket::Websocket() : m_client(std::make_shared<client>())
{
    m_client->init_asio();
    m_client->set_tls_init_handler(std::bind(&Websocket::on_tls_init));
    if (!spdlog::get("logger(websocket)")) {
        spdlog::stdout_color_mt("logger(websocket)");
    }
    logger = spdlog::get("logger(websocket)");
}

context_ptr Websocket::on_tls_init()
{
    context_ptr ctx = websocketpp::lib::make_shared<context>(context::tlsv12);

    try
    {
        ctx->set_options(context::default_workarounds | context::no_sslv2 | context::no_sslv3 | context::single_dh_use);
    }
    catch (std::exception &e)
    {
        std::shared_ptr<spdlog::logger> logger = spdlog::get("logger(websocket)");
        logger->error("Error in context pointer: {}", e.what());
    }

    return ctx;
}

void Websocket::connect(const std::string &uri)
{
    if (m_connections.find(uri) != m_connections.end())
    {
        return;
    }

    websocketpp::lib::error_code ec;
    client::connection_ptr connection = m_client->get_connection(uri, ec);

    if (ec)
    {
        logger->error("Could not create connection because: {}", ec.message());
        return;
    }

    m_client->connect(connection);
    m_connections[uri] = connection;
}

void Websocket::run()
{
    m_client->run();
}
} // namespace Common