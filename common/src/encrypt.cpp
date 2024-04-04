#include <encrypt.hpp>
#include <iomanip>
#include <sstream>

namespace Common::EncryptProtocol
{
std::string HMAC_SHA256::sign(const std::string &secret, const std::string &message)
{
    unsigned char *digest =
        HMAC(EVP_sha256(), secret.c_str(), secret.size(), (unsigned char *)message.c_str(), message.size(), NULL, NULL);

    std::ostringstream os;
    for (int i = 0; i < 32; i++)
    {
        os << std::hex << std::setw(2) << std::setfill('0') << (int)digest[i];
    }

    return os.str();
}
} // namespace EncryptProtocol