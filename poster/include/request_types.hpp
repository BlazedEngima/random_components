#pragma once

#include <cstdint>
#include <unordered_map>

namespace Exchange::HTTPRequest
{

enum class RequestType : uint8_t
{
    POST = 0,
    GET = 1,
    DELETE = 2,
    PUT = 3
};

extern const std::unordered_map<RequestType, const char *> RequestTypeStrings;

} // namespace Exchange::HTTPRequest