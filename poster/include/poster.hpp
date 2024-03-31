#ifndef POSTER_HPP
#define POSTER_HPP

#include <string>
#include <chrono>
#include <nlohmann/json.hpp>
#include <websocket.hpp>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <utils.hpp>
#include <time.hpp>
#include <sstream>

class Poster : public Websocket
{
private:
    std::string api_key;
    std::string api_secret;

    std::string create_request(
        const std::string &id,
        const std::string &symbol,
        const std::string &side,
        const std::string &type,
        const std::string &time_in_force,
        const std::string &quantity,
        const std::string &price);

public:
    Poster(const std::string &api_key, const std::string &api_secret);

    int send(
        const std::string &id,
        const std::string &symbol,
        const std::string &side,
        const std::string &type,
        const std::string &time_in_force,
        const std::string &quantity,
        const std::string &price,
        const std::string &uri);
};

#endif