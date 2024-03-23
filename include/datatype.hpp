#ifndef DATATYPE_HPP
#define DATATYPE_HPP

#include <unordered_map>
#include <memory>
#include <mutex>
#include <vector>
#include <string>

namespace DataType
{

    struct Record
    {
        std::vector<std::pair<double, uint64_t>> data;
        std::mutex mutex;
    };

}

#endif
