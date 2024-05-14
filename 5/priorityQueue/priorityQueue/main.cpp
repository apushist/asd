#include "priorityQueue.h"
#include <chrono>
#include <ctime>


using std::chrono::high_resolution_clock;

void printDurations(high_resolution_clock::time_point t1,
	high_resolution_clock::time_point t2,
	high_resolution_clock::time_point t3,
	high_resolution_clock::time_point t4
	) {
	auto myduration1 = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
	auto myduration2 = std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count();
	auto stdduration = std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count();
	std::cout << "MyPriorityQueue1 duration : " << myduration1 << " ms" << std::endl;
	std::cout << "MyPriorityQueue2 duration : " << myduration2 << " ms" << std::endl;
	std::cout << "std::list duration : " << stdduration << " ms\n\n\n";
}

void testFunc() {


	myPriorityQueue1<int> myq1;
	myPriorityQueue2<int> myq2;
	std::priority_queue<int> stdq;

	SIZE = 20000;

	int* xx = new int[SIZE];
	for (int i = 0; i < SIZE; i++) {
		xx[i] = rand();
	}



	std::cout << "Function: push\n";
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	for (int i = 0; i < SIZE; i++) {
		myq1.push(xx[i]);
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	for (int i = 0; i < SIZE; i++) {
		myq2.push(xx[i]);
	}
	high_resolution_clock::time_point t3 = high_resolution_clock::now();

	for (int i = 0; i < SIZE; i++) {
		stdq.push(xx[i]);
	}
	high_resolution_clock::time_point t4 = high_resolution_clock::now();

	printDurations(t1, t2, t3, t4);


	SIZE = 10000;

	std::cout << "Function: getMax\n";
	t1 = high_resolution_clock::now();

	for (int i = 0; i < SIZE; i++) {
		myq1.getMax();
	}
	t2 = high_resolution_clock::now();

	for (int i = 0; i < SIZE; i++) {
		myq2.getMax();
	}
	t3 = high_resolution_clock::now();

	for (int i = 0; i < SIZE; i++) {
		stdq.top();
		stdq.pop();
	}
	t4 = high_resolution_clock::now();

	printDurations(t1, t2, t3, t4);

	std::cout << "Function: from array\n";
	t1 = high_resolution_clock::now();

	myPriorityQueue1<int> myq11 = myPriorityQueue1<int>(xx, SIZE);
	
	t2 = high_resolution_clock::now();

	myPriorityQueue2<int> myq22 = myPriorityQueue2<int>(xx, SIZE);

	t3 = high_resolution_clock::now();

	std::priority_queue<int> stdq2 = std::priority_queue<int>(xx,xx+SIZE);

	t4 = high_resolution_clock::now();

	printDurations(t1, t2, t3, t4);


	std::cout << "Function: merge\n";
	t1 = high_resolution_clock::now();

	myq1.merge(myq11);
	
	t2 = high_resolution_clock::now();

	myq2.merge(myq22);

	t3 = high_resolution_clock::now();

	merge_pq(stdq, stdq2);
	
	t4 = high_resolution_clock::now();

	printDurations(t1, t2, t3, t4);


	std::cout << "Function: print\n\n";
	t1 = high_resolution_clock::now();

	std::cout << myq1 << "\n\n";

	t2 = high_resolution_clock::now();

	std::cout << myq2 << "\n\n";

	t3 = high_resolution_clock::now();
	while (!stdq.empty()) {
		std::cout << stdq.top();
		stdq.pop();
	}
	std::cout << "\n";

	t4 = high_resolution_clock::now();

	printDurations(t1, t2, t3, t4);
}

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

	//testFunc();

	setlocale(LC_ALL, "Russian");

	std::priority_queue<int> pq;
	pq.push(0);
	pq.push(42);
	std::cout << pq.top() << "\n";

	std::string filename = "voinaIMir.txt";

	myPriorityQueue2<std::string, std::deque<std::string>, StringLengthComp> q;

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	getWordsFromFile(filename, q);
	std::cout << "\n20 самых длинных слов из текста:\n";
	print20Max(q);

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto myduration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
	std::cout << "\nduration: " << myduration << " ms";

}
