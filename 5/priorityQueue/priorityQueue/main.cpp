#include "priorityQueue.h"

int main() {
	std::vector<std::string> v;
	v.push_back("gdsjj");
	v.push_back("affff");
	v.push_back("asdfghjkl;");
	v.push_back("bsdfghjkl;");
	std::sort(v.begin(), v.end());
	for (std::string x : v) {
		//std::cout << x << " ";
	}
	//std::cout << "\n" << v.front() << " " << v.back();

	myPriorityQueue1<std::string, std::deque<std::string>, StringLengthComp> q;
	q.push("a");
	std::string* arr = new std::string[4]{"ydythf","ggjhgjh","juu","asdfghjkl;defghjk"};

	q.pushFromArray(arr,4);
	//q.println();
	//std::cout << q.getMax();
	std::deque<int> d;
	

	myPriorityQueue1<int> q1;
	myPriorityQueue1<int> q2;
	
	q1.push({ 1, 12, 3, 4, 25, 6 });
	q2.push({ 7,5,2,11,16 });

	q1.println();



}