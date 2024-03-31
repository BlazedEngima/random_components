#ifndef LISTENER_HPP
#define LISTENER_HPP

#include <websocket.hpp>
#include <msg_handler.hpp>

class Listener : public Websocket
{
private:
    std::shared_ptr<book> m_book;

public:
    Listener(std::shared_ptr<book> &ledger) : m_book(ledger)
    {
        m_client->set_message_handler(
            [this](websocketpp::connection_hdl hdl_connection, client::message_ptr message)
            { MsgHandler::on_message(m_client.get(), hdl_connection.lock(), message, m_book); });
    }
};

#endif