#ifndef DATATYPE_HPP
#define DATATYPE_HPP

#include <memory>
#include <mutex>
#include <vector>
#include <string>
#include <utility>
#include <unordered_map>

namespace DataType
{

    struct Record
    {
        std::vector<std::pair<double, uint64_t>> data;
        std::mutex mutex;
    };

}

#endif
