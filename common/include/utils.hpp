// utils.hpp
#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <sstream>
#include <iomanip>
#include <openssl/hmac.h>

namespace Utils
{
    namespace Sign
    {
        std::string hmac_sha256(const std::string &key, const std::string &payload);
    }
}

#endif