#pragma once

#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <string>

namespace Common::EncryptProtocol
{
class HMAC_SHA256
{
  public:
    static std::string sign(const std::string &secret, const std::string &message);
};
} // namespace EncryptProtocol