#pragma once

#include <mutex>
#include <utility>
#include <vector>

namespace DataType {

struct Record {
    std::vector<std::pair<double, uint64_t>> data;
    std::mutex mutex;
};

} // namespace DataType