#include <utils.hpp>

namespace Utils
{
    namespace Sign
    {
        std::string hmac_sha256(
            const std::string &key,
            const std::string &payload)
        {
            unsigned char *digest;
            digest = HMAC(EVP_sha256(),
                          key.c_str(),
                          key.length(),
                          (unsigned char *)payload.c_str(),
                          payload.length(),
                          NULL,
                          NULL);

            std::ostringstream os;
            for (int i = 0; i < 32; i++)
            {
                os << std::hex
                   << std::setw(2)
                   << std::setfill('0')
                   << (int)digest[i];
            }

            return os.str();
        }
    }
}