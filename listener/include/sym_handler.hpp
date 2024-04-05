#pragma once

#include <string>

namespace Listener::Handler::Symbol::Binance
{
static std::string transform(const std::string &symbol)
{
    std::string lower_case = symbol;
    lower_case.reserve(symbol.size() + 9); // Reserve enough space for the original string, the
                                           // underscore, and "_futures"
    std::transform(lower_case.begin(), lower_case.end(), lower_case.begin(), ::tolower);
    lower_case.insert(lower_case.rfind('u'), "_");
    lower_case.append("_futures");
    return lower_case;
}
} // namespace Listener::Handler::Symbol::Binance