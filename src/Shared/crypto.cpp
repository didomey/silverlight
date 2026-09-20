#include <string>

void xor_crypt(std::string &key, std::string &data)
{
    for (int i = 0; i < data.size(); i++)
        data[i] ^= key[ i % key.size() ];
}
