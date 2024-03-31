#include <poster.hpp>

Poster::Poster(const std::string &api_key, const std::string &api_secret)
    : api_key(api_key), api_secret(api_secret)
{
    m_client->clear_access_channels(websocketpp::log::alevel::all);
    m_client->set_error_channels(websocketpp::log::elevel::all);
    m_client->set_message_handler([this](websocketpp::connection_hdl hdl, client::message_ptr msg)
                                  { std::cout << "payload:" << std::endl;
                                    nlohmann::json payload = nlohmann::json::parse(msg->get_payload());
                                    std::cout << payload.dump(4) << std::endl; });
}

std::string Poster::create_request(
    const std::string &id,
    const std::string &symbol,
    const std::string &side,
    const std::string &type,
    const std::string &time_in_force,
    const std::string &quantity,
    const std::string &price)
{
    std::ostringstream oss;
    oss << "apiKey=" << api_key
        << "&newOrderRespType=ACK"
        << "&price=" << price
        << "&quantity=" << quantity
        << "&recvWindow=" << 5000
        << "&side=" << side
        << "&symbol=" << symbol
        << "&timeInForce=" << time_in_force
        << "&timestamp=" << std::to_string(Time::Now::milliseconds().count())
        << "&type=" << type;

    std::string payload = oss.str();

    std::istringstream iss(payload);
    std::string pair;
    nlohmann::json params;

    while (std::getline(iss, pair, '&'))
    {
        std::istringstream pair_stream(pair);
        std::string key, value;
        std::getline(pair_stream, key, '=');
        std::getline(pair_stream, value);
        params[key] = value;
    }

    std::string signature = Utils::Sign::hmac_sha256(api_secret, payload);
    params["signature"] = signature;

    nlohmann::json request;
    request["id"] = id;
    request["method"] = "order.place";
    request["params"] = std::move(params);

    return request.dump();
}

int Poster::send(
    const std::string &id,
    const std::string &symbol,
    const std::string &side,
    const std::string &type,
    const std::string &time_in_force,
    const std::string &quantity,
    const std::string &price,
    const std::string &uri)
{
    std::string request = create_request(
        id,
        symbol,
        side,
        type,
        time_in_force,
        quantity,
        price);

    m_client->send(
        m_connections[uri],
        request,
        websocketpp::frame::opcode::text);

    return 0;
}