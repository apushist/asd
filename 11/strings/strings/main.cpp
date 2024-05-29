#include "rabin_karp.h"

#include <iostream>

int main() {
	const char* str = "aaaaa";
	const char* substr = "a";

	std::vector<int> v = rabin_karp_search(str, substr);
	for (int x : v)
		std::cout << x << " ";
}


