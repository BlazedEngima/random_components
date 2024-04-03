#ifndef DB_HANDLER_HPP
#define DB_HANDLER_HPP

#include <queue>
#include <mutex>
#include <mysqlx/xdevapi.h>

class DBHandler
{
public:
    DBHandler(
        const std::string &host,
        const std::string &user,
        const std::string &password,
        const std::string &db_name,
        const int &port,
        const size_t &pool_size = 4);

    void insert_to_db(const std::string &symbol, const double &price, const u_int64_t &time);
    ~DBHandler();

private:
    std::queue<mysqlx::Session*> sessions;
    const std::string db_name;
    std::mutex mutex;
};

#endif