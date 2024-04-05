#pragma once

#include <memory>
#include <mutex>
#include <mysqlx/xdevapi.h>
#include <queue>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Common
{

class DBHandler
{
  public:
    DBHandler(const std::string &host, const std::string &user, const std::string &password, const std::string &db_name,
              const int port, const size_t pool_size);

    virtual ~DBHandler();

  protected:
    std::queue<mysqlx::Session *> sessions;
    const std::string db_name;
    std::mutex mutex;
    std::shared_ptr<spdlog::logger> logger;
};

} // namespace Common