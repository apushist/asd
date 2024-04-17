#include "priorityQueue.h"

int main() {
	std::vector<std::string> v;
	v.push_back("gdsjj");
	v.push_back("affff");
	v.push_back("asdfghjkl;");
	v.push_back("bsdfghjkl;");
	std::sort(v.begin(), v.end());
	for (std::string x : v) {
		std::cout << x << " ";
	}
	std::deque<int> d;
	
}