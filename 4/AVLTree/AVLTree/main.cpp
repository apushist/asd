#include "avl.h"
#include <vector>

int main() {
	//AVLTree<int> tree;
	////std::cout << tree.empty();

	//tree.insert(5);
	//tree.insert(7);
	//for (auto it = tree.begin(); it != tree.end();it++) {
	//	//std::cout << it.getValue() <<"\n";
	//}
	//tree.clear();

	//AVLTree<int> tree2 = { 40,50,30,35,10,75,23,87,68, 48 };

	//AVLTree<int> T1 = { 40,50,30,35,10,75,23,87,68 };
	//AVLTree<int> T2;
	//T2 = T1;
	//T1.printLKP();
	//T2.printLKP();

	//T1.clear();
	//T2 = T1;
	//T1.printLKP();
	//T2.printLKP();

	//
	//std::cout << (T1 == T2);


	mySet<std::string> T1{ "abc", "cde", "123", "AAAAAAAA" };
	std::vector<std::string> check1{ "123", "AAAAAAAA", "abc", "cde" };

	
	for (const auto& str : check1)
		T1.erase(str);

	char carr[] = "abcdef";

	mySet<char>	v1(carr, carr + 3);

	std::cout << v1.count('b');
	auto pcc = v1.equal_range('a');

	std::cout << *v1.erase(v1.begin()) << " __  " << v1.size();
}