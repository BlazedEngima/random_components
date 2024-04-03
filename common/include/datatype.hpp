#pragma once

#include <mutex>
#include <utility>
#include <vector>

namespace Common::DataType
{

struct Record
{
    std::vector<std::pair<double, uint64_t>> data;
    std::mutex mutex;
};

} // namespace Common::DataType