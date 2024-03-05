#include "tree.h"


int main() {
	Tree<int> tr;
	tr.insert(25);
	tr.insert(28);
	tr.insert(14);
	tr.insert(18);
	tr.insert(15);
	tr.insert(10);
	tr.insert(30);
	tr.insert(-45);
	tr.insert(12);
	tr.insert(-16);
	tr.insert(-29);
	tr.insert(34);



	Tree<int> tr2;
	tr2.insert(25);
	tr2.insert(28);
	tr2.insert(14);
	tr2.insert(18);
	tr2.insert(15);
	tr2.insert(10);
	tr2.insert(3);
	tr2.insert(45);
	tr2.insert(12);
	tr2.insert(16);
	tr2.insert(29);
	tr2.insert(34);

	Tree<int>::Node* n = tr.previous(tr.find(28));
	tr.printLKP();
	tr.deleteElem(10);
	tr.printLKP();
	tr.deleteElem(16);
	tr.printLKP();
	tr.deleteElem(25);
	std::cout << "Prints:\n\n";
	tr.printLKP();
	tr.printPKL();
	tr.printLevels();
	std::cout << "\n\n";
	std::cout << "tr.find(12): " << *(tr.find(12)) << "\n";
	std::cout << "tr.find(122) == nullptr: " << (tr.find(122) == nullptr) << "\n";
	std::cout << "tr.findMax(): " << *tr.findMax() << "\n";
	std::cout << "tr.findMin(): " << *tr.findMin() << "\n";
	std::cout << "tr.upperBound(25): " << *tr.upperBound(25) << "\n";
	std::cout << "tr.upperBound(26): " << *tr.upperBound(26) << "\n";
	std::cout << "tr.lowerBound(25): " << *tr.lowerBound(25) << "\n";
	std::cout << "tr.lowerBound(26): " << *tr.lowerBound(26) << "\n";
	std::cout << "tr.previous(tr.find(28)): " << *tr.previous(tr.find(28)) << "\n";
	std::cout << "tr.next(tr.find(28)): " << *tr.next(tr.find(28)) << "\n";
	std::cout << "(tr == tr2): " << (tr == tr2) << "\n";
	std::cout << "(tr == tr): " << (tr == tr) << "\n";
}