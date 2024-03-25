#ifndef SYM_HANDLER_HPP
#define SYM_HANDLER_HPP

#include <string>

namespace SymHandler
{
    namespace Binance
    {
        static std::string transform(const std::string &symbol)
        {
            std::string lower_case = symbol;
            std::transform(lower_case.begin(), lower_case.end(), lower_case.begin(), ::tolower);
            lower_case.insert(lower_case.find('u'), "_");
            return lower_case;
        }
    }
}

#endif