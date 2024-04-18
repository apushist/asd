#include "tasks.h"

int main() {
	//generateInput("input.txt", 10000, 30);
	std::vector<int> v = task1("input.txt");
	for (int x : v)
		std::cout << x << " ";
}