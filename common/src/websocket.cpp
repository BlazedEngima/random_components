#include <websocket.hpp>

Websocket::Websocket(std::shared_ptr<book> &ledger) : m_client(std::make_shared<client>()),
                                                      m_book(ledger)
{
    m_client->init_asio();
    m_client->set_tls_init_handler(
        std::bind(&Websocket::on_tls_init));
}

context_ptr Websocket::on_tls_init()
{
    context_ptr ctx = websocketpp::lib::make_shared<context>(context::tlsv12);

    try
    {
        ctx->set_options(context::default_workarounds |
                         context::no_sslv2 |
                         context::no_sslv3 |
                         context::single_dh_use);
    }
    catch (std::exception &e)
    {
        std::cout << "Error in context pointer: " << e.what() << std::endl;
    }

    return ctx;
}

void Websocket::connect(const std::string &uri)
{
    websocketpp::lib::error_code ec;
    client::connection_ptr connection = m_client->get_connection(uri, ec);

    if (ec)
    {
        std::cout << "Could not create connection because: " << ec.message() << std::endl;
        return;
    }

    m_client->connect(connection);
}

void Websocket::run()
{
    m_client->run();
}