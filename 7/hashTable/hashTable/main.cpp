#include "hashTable.h"
#include <chrono>
#include <ctime>
#include <unordered_set>


using std::chrono::high_resolution_clock;

int SIZE = 204800;

void printDurations(high_resolution_clock::time_point t1,
	high_resolution_clock::time_point t2,
	high_resolution_clock::time_point t3
) {
	auto myduration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
	auto stdduration = std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count();
	std::cout << "HashTable duration : " << myduration << " ms" << std::endl;
	std::cout << "std::unordered_multiset duration : " << stdduration << " ms\n\n\n";
}

void testFunc() {

	HashTable ht(SIZE/2);
	std::unordered_multiset<int> multis;


	int* xx = new int[SIZE];
	for (int i = 0; i < SIZE; i++) {
		xx[i] = rand();
	}

	std::cout << "Function: insert\n";
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	for (int i = 0; i < SIZE; i++) {
		ht.insert(xx[i]);
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	for (int i = 0; i < SIZE; i++) {
		multis.insert(xx[i]);
	}
	high_resolution_clock::time_point t3 = high_resolution_clock::now();

	printDurations(t1, t2, t3);


	std::cout << "Function: contains\\find\n";
	t1 = high_resolution_clock::now();

	for (int i = SIZE; i >= 0; i--) {
		ht.contains(xx[i]);
	}

	t2 = high_resolution_clock::now();

	for (int i = SIZE; i >= 0; i--) {
		multis.find(xx[i]);
	}

	t3 = high_resolution_clock::now();

	printDurations(t1, t2, t3);


	std::cout << "Function: remove\\erase\n";
	t1 = high_resolution_clock::now();

	for (int i = 0; i < SIZE/2; i++) {
		ht.remove(xx[i]);
	}
	t2 = high_resolution_clock::now();

	for (int i = 0; i < SIZE/2; i++) {
		multis.erase(xx[i]);
	}
	t3 = high_resolution_clock::now();

	printDurations(t1, t2, t3);
}



int main() {
	HashTable ht(5);

	ht.insert(12);
	ht.insert(33);
	ht.insert(112);
	ht.insert(312);
	ht.insert(311);
	ht.insert(310);
	ht.insert(312);
	ht.insert(77);
	ht.insert(67);

	ht.remove(33);
	ht.remove(67);

	std::cout << ht << "\n";

	//ht.remove(312);

	//std::cout << ht;

	testFunc();
}