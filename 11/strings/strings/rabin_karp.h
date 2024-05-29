#pragma once
#include <vector>

unsigned long long hashFunction(const char* str);

std::vector<int> rabin_karp_search(const char* str, const char* substr);
