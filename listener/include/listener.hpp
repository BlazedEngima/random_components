#pragma once

#include <msg_handler.hpp>
#include <websocket.hpp>

class Listener : public Websocket {
private:
    std::shared_ptr<book> m_book;

public:
    Listener(std::shared_ptr<book>& ledger)
        : m_book(ledger)
    {
        m_client->set_message_handler(
            [this](
                websocketpp::connection_hdl /*hdl_connection*/,
                client::message_ptr message) {
                MsgHandler::on_message(message, m_book);
            });
    }
};