#pragma once

#include <db_handler.hpp>
#include <mysqlx/devapi/result.h>
#include <vector>

namespace Poster::DB
{
class Reader : public Common::DBHandler
{
  public:
    std::vector<mysqlx::Row> read(const std::string &table_name);
};

} // namespace Poster::DB