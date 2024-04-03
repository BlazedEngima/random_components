#pragma once

#include <commons.hpp>

struct MsgHandler {
    static void on_message(
        client::message_ptr message,
        const std::shared_ptr<book>& logbook)
    {
        nlohmann::json payload = nlohmann::json::parse(message->get_payload());

        if (payload.find("e") != payload.end() && payload["e"] == "trade") {
            std::string symbol = payload["s"].get<std::string>();
            std::lock_guard<std::mutex> lock((*logbook)[symbol].mutex);
            (*logbook)[symbol].data.push_back(
                std::make_pair(std::stod(payload["p"].get<std::string>()),
                    payload["T"].get<uint64_t>()));
        }
    }
};