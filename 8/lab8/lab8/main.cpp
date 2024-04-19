#include "tasks.h"

int main() {
	std::cout << "TASK 1:\n";
	//generateInput("input.txt", 10000, 30);
	//generateInput("input2.txt", 10, 5);
	std::vector<int> v = task1("input.txt");
	for (int x : v)
		std::cout << x << " ";

	std::cout << "\n\nTASK 2:\n";
	setlocale(LC_ALL, "Russian");

	std::string str = "Дана строка S, и константа N. Необходимо разбить исходную строку на подстроки, не превосходящие по длине N, с учетом того, что эти подстроки должны быть выровнены «по ширине» до размера N.";
	std::vector<std::string> formStr = task15(str, 30);

	for (std::string x : formStr)
		std::cout << x << "\n";
}