#ifndef COMPUTE_HPP
#define COMPUTE_HPP

#include <vector>
#include <numeric>
#include <utility>

namespace Compute
{
    namespace Average
    {
        static double minute(const std::vector<std::pair<double, uint64_t>> &vec)
        {
            double sum = std::accumulate(vec.begin(), vec.end(), 0.0,
                                         [](double acc, const std::pair<double, uint64_t> &p)
                                         {
                                             return acc + p.first;
                                         });

            return sum / vec.size();
        }
    }
}

#endif