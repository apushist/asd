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
	tr.insert(45);
	tr.insert(12);
	tr.insert(16);
	tr.insert(29);
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

	//Tree<int>::Node* n = tr.previous(tr.find(28));
	tr.printLKP();
	/*tr.deleteElem(10);
	tr.printLKP();
	tr.deleteElem(16);
	tr.printLKP();
	tr.deleteElem(25);
	tr.printLKP();*/
	tr.printPKL();
	//tr.printLevels();
	//std::cout << (tr == tr2);
}