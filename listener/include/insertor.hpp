#pragma once

#include <db_handler.hpp>

namespace Listener::DB
{

class Insertor : public Common::DBHandler
{
  public:
    void insert_to_db(const std::string &symbol, const double price, const uint64_t time);

    Insertor(const std::string &host, const std::string &user, const std::string &password, const std::string &db_name,
             const int port, const size_t pool_size);
};

} // namespace Listener::DB