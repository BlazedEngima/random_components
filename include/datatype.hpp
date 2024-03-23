#ifndef DATATYPE_HPP
#define DATATYPE_HPP

#include <unordered_map>
#include <memory>
#include <mutex>
#include <vector>
#include <string>

namespace DataType {

    struct Record {
        std::vector<std::pair<double, double>> data;
        std::mutex mutex;
    };

}

using book = std::unordered_map<std::string, DataType::Record>;

#endif
