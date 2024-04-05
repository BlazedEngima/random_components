#pragma once

#include <msg_handler.hpp>
#include <websocket.hpp>

namespace Components
{

class Listener : public Common::Websocket
{
  public:
    Listener(std::shared_ptr<Common::book> &ledger) : m_book(ledger)
    {
        m_client->set_message_handler(
            [this](websocketpp::connection_hdl /*hdl_connection*/, Common::client::message_ptr message) {
                ::Listener::Handler::Msg::on_message(message, m_book);
            });
    }

  private:
    std::shared_ptr<Common::book> m_book;
};

} // namespace Components