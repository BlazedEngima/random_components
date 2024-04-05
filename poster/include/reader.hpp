#pragma once

#include <db_handler.hpp>

namespace Poster::DB {
    class Reader: public Common::DBHandler {
        public:
            void read_from_db(const std::string &symbol, const uint64_t start_time, const uint64_t end_time);
    };
}