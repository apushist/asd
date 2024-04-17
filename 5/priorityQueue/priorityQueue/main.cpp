#include "priorityQueue.h"

int main() {
	//std::vector<std::string> v;
	//v.push_back("gdsjj");
	//v.push_back("affff");
	//v.push_back("asdfghjkl;");
	//v.push_back("bsdfghjkl;");
	//std::sort(v.begin(), v.end());
	//for (std::string x : v) {
	//	//std::cout << x << " ";
	//}
	////std::cout << "\n" << v.front() << " " << v.back();

	//myPriorityQueue1<std::string, std::deque<std::string>, StringLengthComp> q;
	//q.push("a");
	//std::string* arr = new std::string[4]{"ydythf","ggjhgjh","juu","asdfghjkl;defghjk"};

	//q = myPriorityQueue1<std::string, std::deque<std::string>, StringLengthComp>(arr,4);
	////q.println();
	////std::cout << q.getMax();
	//std::deque<int> d = {12,2,3,4};
	//
	////std::cout << v[0];
	//

	//myPriorityQueue2<int> q1 = myPriorityQueue2<int>(new int[6]{ 1, 12, 3, 4, 25, 6 },6);
	//myPriorityQueue2<int> q2 = myPriorityQueue2<int>(new int[5] { 7, 5, 2, 11, 16 }, 5);
	//

	//q1.println();
	//q2.println();

	//q1.merge(q2);

	//q1.println();
	//std::cout << q1.getMax() << "\n";
	//q1.println();
	setlocale(LC_ALL, "Russian");

	std::string filename = "lotr.txt";

	myPriorityQueue1<std::string, std::deque<std::string>, StringLengthComp> q1;
	myPriorityQueue2<std::string, std::deque<std::string>, StringLengthComp> q2;


	getWordsFromFile(filename, q1);
	std::cout << "ÐÅÀËÈÇÀÖÈß 1:\n";
	print20Max(q1);

	getWordsFromFile(filename, q2);
	std::cout << "\n\nÐÅÀËÈÇÀÖÈß 2:\n";	
	print20Max(q2);

}