#include <time.hpp>

namespace Time
{
    namespace Now
    {
        std::chrono::milliseconds milliseconds()
        {
            return std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch());
        }
    }
}