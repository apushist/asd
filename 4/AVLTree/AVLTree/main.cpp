#include "avl.h"
#include <vector>
#include <chrono>
#include <ctime>
#include <set>

using std::chrono::high_resolution_clock;
const int SIZE = 10000;

void printDurations(high_resolution_clock::time_point t1,
	high_resolution_clock::time_point t2,
	high_resolution_clock::time_point t3) {
	auto myduration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
	auto stdduration = std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count();
	std::cout << "MySet duration : " << myduration << " ms" << std::endl;
	std::cout << "std::set duration : " << stdduration << " ms\n\n\n";
}

void testFunct() {
	mySet<int> mySet;
	std::set<int> stSet;

	std::vector<int> xx;
	for (int i = 0; i < SIZE; i++) {
		xx.push_back(rand());
	}


	std::cout << "Function: insert\n";
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	for (int i = 0; i < SIZE; i++) {
		mySet.insert(xx[i]);
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	for (int i = 0; i < SIZE; i++) {
		stSet.insert(xx[i]);
	}
	high_resolution_clock::time_point t3 = high_resolution_clock::now();

	printDurations(t1, t2, t3);
}


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

	AVLTree<int> T1 = { 40,50,30,35,10,75,23,87 };
	//AVLTree<int> T2;
	//T2 = T1;
	//T1.printLKP();
	//T2.printLKP();
	T1.insert(87);
	std::cout << T1.getCountOfRotates() << "\n";
	T1.insert(68);
	std::cout << T1.getCountOfRotates() << "\n";
	T1.printLevels();
	T1.saveInFile("file.txt");
	//T1.clear();
	//T2 = T1;
	//T1.printLKP();
	//T2.printLKP();

	//
	//std::cout << (T1 == T2);


	/*mySet<std::string> T1{ "abc", "cde", "123", "AAAAAAAA" };
	std::vector<std::string> check1{ "123", "AAAAAAAA", "abc", "cde" };

	
	for (const auto& str : check1)
		T1.erase(str);

	char carr[] = "abcdef";

	mySet<char>	v1(carr, carr + 3);

	std::cout << v1.count('b');
	auto pcc = v1.equal_range('a');

	std::cout << *v1.erase(v1.begin()) << " __  " << v1.size();*/

	//testFunct();
}