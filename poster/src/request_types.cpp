#include <request_types.hpp>

namespace Exchange::HTTPRequest
{
const std::unordered_map<RequestType, const char *> RequestTypeStrings = {
    {RequestType::POST, "POST"}, {RequestType::GET, "GET"}, {RequestType::DELETE, "DELETE"}, {RequestType::PUT, "PUT"}};
}