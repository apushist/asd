#include "rabin_karp.h"


const int k = 31, mod = 1e9 + 7;

unsigned long long hashFunction(const char* str) {
    unsigned long long hash = 0;
    int c;
    while ((c = *str++)) {
        int x = (int)(c - 'a' + 1);
        hash = (hash * k + x) % mod;
    }

    return hash;
}

std::vector<int> rabin_karp_search(const char* str, const char* substr)
{
    int hash;

    std::vector<int> result;

    unsigned int strLength = strlen(str);
    unsigned int substrLength = strlen(substr);

    unsigned long long strHash = hashFunction(str);
    unsigned long long substrHash = hashFunction(substr);

    for (int i = 0; i <= strLength - substrLength; i++) {
        if (strHash == substrHash)
        {
            for (unsigned int k = 0; (k < substrLength) && (substr[k] == str[i + k]); k++) {
                if (k == (substrLength - 1)) {
                    result.push_back(i);
                }
            }
        }

        
        strHash = (p * strHash - pow(p, substrLength) * hashFunction(str[i]) + hashFunction(str[i + substrLength])) % r;
    }

    return result;
}
