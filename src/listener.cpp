#include <listener.hpp>

Listener::Listener(std::shared_ptr<book> &ledger) : m_client(std::make_shared<client>()),
                                                    m_book(ledger)
{
    m_client->init_asio();
    m_client->set_tls_init_handler(
        std::bind(&Listener::on_tls_init));
    m_client->set_message_handler([this](websocketpp::connection_hdl hdl_connection, client::message_ptr message)
                                  { MsgHandler::on_message(m_client.get(), hdl_connection.lock(), message, m_book); });
}

context_ptr Listener::on_tls_init()
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

void Listener::connect(const std::string &uri)
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

void Listener::run() {
    m_client->run();
}