#pragma once

#include <numeric>
#include <utility>
#include <vector>

namespace Compute::Average {

static double
minute(const std::vector<std::pair<double, uint64_t>>& vec)
{
    double sum = std::accumulate(vec.begin(),
        vec.end(),
        0.0,
        [](double acc, const std::pair<double, uint64_t>& p) {
            return acc + p.first;
        });

    return sum / vec.size();
}
} // namespace Compute::Average
