#include "avl.h"

int main() {
	AVLTree<int> tree;
	//std::cout << tree.empty();

	tree.insert(5);
	tree.insert(7);
	for (auto it = tree.begin(); it != tree.end();it++) {
		//std::cout << it.getValue() <<"\n";
	}
	tree.clear();

	AVLTree<int> tree2 = { 40,50,30,35,10,75,23,87,68, 48 };

	AVLTree<int> T1 = { 40,50,30,35,10,75,23,87,68 };
	AVLTree<int> T2;
	T2 = T1;
	T1.printLKP();
	T2.printLKP();

	T1.clear();
	T2 = T1;
	T1.printLKP();
	T2.printLKP();

	
	std::cout << (T1 == T2);
}