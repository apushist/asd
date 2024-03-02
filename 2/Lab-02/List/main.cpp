
#include <list>
#include "my_list.h"
#include <vector>
#include <string>
#include <chrono>
#include <ctime>

using std::chrono::high_resolution_clock;

const int SIZE = 1000000;

void printDurations(high_resolution_clock::time_point t1, 
	high_resolution_clock::time_point t2,
	high_resolution_clock::time_point t3) {
	auto myduration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
	auto stdduration = std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count();
	std::cout << "MyList duration : " << myduration << " ms" << std::endl;
	std::cout << "std::list duration : " << stdduration << " ms\n\n\n";
}

//  Функция для тестирования времени работы функций
//    последовательно запускает функцию f для всех значений из интервала [ start; start+len )
//    и выводит время работы
void testFunct() {
	MyList<int> my_list;
	std::list<int> list;


	std::vector<int> xx;
	for (int i = 0; i < SIZE; i++) {
		xx.push_back(rand());
	}

	std::cout << "Function: push_back\n";
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	for (int i = 0; i < SIZE; i++) {
		my_list.push_back(xx[i]);
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	
	for (int i = 0; i < SIZE; i++) {
		list.push_back(xx[i]);
	}
	high_resolution_clock::time_point t3 = high_resolution_clock::now();

	printDurations(t1,t2,t3);

	std::cout << "Function: push_front\n";
	t1 = high_resolution_clock::now();
	for (int i = 0; i < SIZE; i++) {
		my_list.push_front(xx[i]);
	}
	t2 = high_resolution_clock::now();
	
	for (int i = 0; i < SIZE; i++) {
		list.push_front(xx[i]);
	}
	t3 = high_resolution_clock::now();

	printDurations(t1, t2, t3);


	std::cout << "Function: front\n";
	t1 = high_resolution_clock::now();
	for (int i = 0; i < SIZE; i++) {
		my_list.front();
	}
	t2 = high_resolution_clock::now();
	for (int i = 0; i < SIZE; i++) {
		list.front();
	}
	t3 = high_resolution_clock::now();
	printDurations(t1, t2, t3);

	std::cout << "Function: back\n";
	t1 = high_resolution_clock::now();
	for (int i = 0; i < SIZE; i++) {
		my_list.back();
	}
	t2 = high_resolution_clock::now();
	for (int i = 0; i < SIZE; i++) {
		list.back();
	}
	t3 = high_resolution_clock::now();
	printDurations(t1, t2, t3);

	std::cout << "Function: empty\n";
	t1 = high_resolution_clock::now();
	for (int i = 0; i < SIZE; i++) {
		my_list.empty();
	}
	t2 = high_resolution_clock::now();
	for (int i = 0; i < SIZE; i++) {
		list.empty();
	}
	t3 = high_resolution_clock::now();
	printDurations(t1, t2, t3);

	std::cout << "Function: size\n";
	t1 = high_resolution_clock::now();
	for (int i = 0; i < SIZE; i++) {
		my_list.size();
	}
	t2 = high_resolution_clock::now();
	for (int i = 0; i < SIZE; i++) {
		list.size();
	}
	t3 = high_resolution_clock::now();
	printDurations(t1, t2, t3);

	std::cout << "Function: insert\n";
	t1 = high_resolution_clock::now();
	auto mypos = std::find(my_list.begin(), my_list.end(), xx[24000]);
	for (int i = 0; i < SIZE; i++) {
		mypos = my_list.insert(mypos,23456);
	}
	t2 = high_resolution_clock::now();
	auto pos = std::find(list.begin(), list.end(), xx[24000]);
	for (int i = 0; i < SIZE; i++) {
		pos = list.insert(pos, 23456);
	}
	t3 = high_resolution_clock::now();
	printDurations(t1, t2, t3);

	std::cout << "Function: erase\n";
	t1 = high_resolution_clock::now();
	my_list.erase(std::find(my_list.begin(), my_list.end(), xx[240]), std::find(my_list.begin(), my_list.end(), xx[3000]));
	t2 = high_resolution_clock::now();
	list.erase(std::find(list.begin(), list.end(), xx[240]), std::find(list.begin(), list.end(), xx[3000]));
	t3 = high_resolution_clock::now();
	printDurations(t1, t2, t3);

	std::cout << "Function: pop_back\n";
	t1 = high_resolution_clock::now();
	for (int i = 0; i < SIZE; i++) {
		my_list.pop_back();
	}
	t2 = high_resolution_clock::now();
	for (int i = 0; i < SIZE; i++) {
		list.pop_back();
	}
	t3 = high_resolution_clock::now();
	printDurations(t1, t2, t3);

	std::cout << "Function: pop_front\n";
	t1 = high_resolution_clock::now();
	for (int i = 0; i < SIZE; i++) {
		my_list.pop_front();
	}
	t2 = high_resolution_clock::now();
	for (int i = 0; i < SIZE; i++) {
		list.pop_front();
	}
	t3 = high_resolution_clock::now();
	printDurations(t1, t2, t3);


	MyList<int> my_swap_list;
	std::list<int> swap_list;

	for (int i = 0; i < SIZE; i++) {
		my_swap_list.push_back(rand());
		swap_list.push_back(rand());
	}

	std::cout << "Function: swap\n";
	t1 = high_resolution_clock::now();
	for (int i = 0; i < SIZE; i++)
		my_list.swap(my_swap_list);
	t2 = high_resolution_clock::now();
	for (int i = 0; i < SIZE; i++)
		list.swap(swap_list);
	t3 = high_resolution_clock::now();
	printDurations(t1, t2, t3);

	std::cout << "Function: clear\n";
	t1 = high_resolution_clock::now();
	my_list.clear();
	t2 = high_resolution_clock::now();
	list.clear();
	t3 = high_resolution_clock::now();
	printDurations(t1, t2, t3);
}



int main(int argc, char** argv)
{
	srand(static_cast<unsigned int>(time(NULL)));

	testFunct();
	
}

