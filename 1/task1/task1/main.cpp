#include "elem.h"
#include "task3.h"

#include <time.h>

#pragma intrinsic(__rdtsc)

using namespace std;
using namespace chrono;

size_t elem::count_of_comp = 0;
size_t elem::count_of_copy = 0;



void my_sort(vector<elem> v) {
	for (int i = 0; i < v.size();i++) {
		for (int j = i; j > 0 && v[j - 1] > v[j];j--) {
			elem t = v[j - 1];
			v[j - 1] = v[j];
			v[j] = t;
		}
			
	}
}

//Сколько существует четных чисел, двоичное представление которых содержит N значащих цифр, для которых выполняется
// правило: в двоичной записи числа не встречается подряд два нуля? Для каких значений N можно получить решение?
long long task2(int n) {
	if (n == 2 || n == 3)
		return 1;
	long long ones = 1;
	long long zeros = 1;
	for (int i = 1; i < n - 3;i++) {
		long long t = ones;
		ones += zeros;
		zeros = t;
	}
	return ones + zeros;
}

long long task4() {
	long long ordinary = 5;
	long long dest = 9;
	for (int i = 1; i < 9;i++) {
		
		long long t = ordinary;
		ordinary = dest * 6;
		dest = ordinary + t * 4;
		
	}
	dest = dest * 4 + ordinary;
	return dest;
}

bool is_prime(int n) {
	return n == 2 || n == 3 || n == 5 || n == 7;
}

long long vlob() {//для проверки алгоритма
	long long count = 0;
	for (long long i = 10000; i < 100000; i+=2) {
		long long n = i;
		bool isPreviousPrime = is_prime(n % 10);
		n /= 10;
		bool hasPrimeNear = false;
		while (n > 0) {
			if (is_prime(n % 10) && isPreviousPrime)
			{
				hasPrimeNear = true;
				break;
			}
			isPreviousPrime = is_prime(n % 10);
			n /= 10;
		}
		if (!hasPrimeNear)
			count++;
	}
	return count;
}




int main() {

	setlocale(LC_ALL, "Russian");

	//Task1----------------------------------------------------------------

	srand(static_cast<unsigned int>(time(NULL)));

	vector<elem> v1(1000), v2(v1);

	cout << "Задание 1\nВекторы созданы: " << v1.size() << " элементов\n";
	cout << "Операций копирования: " << elem::count_of_copy << ", операций сравнения: " << elem::count_of_comp << endl;

	elem::reset();
	my_sort(v1);

	cout << "\nСортировка вставками\nОпераций копирования: " << elem::count_of_copy << ", операций сравнения: " << elem::count_of_comp <<  endl;

	elem::reset();
	sort(v2.begin(), v2.end());


	cout << "\nСортировка стандартным алгоритмом\nОпераций копирования: " << elem::count_of_copy << ", операций сравнения: " << elem::count_of_comp << "\n\n";

	//Task2----------------------------------------------------------------

	cout << "Задание 2\nN = 2: " << task2(2) << "\nN = 3: " << task2(3) << "\nN = 4: " << task2(4) << "\nN = 5: " << task2(5) << "\nN = 50: " << task2(50) << "\n";


	//Task3----------------------------------------------------------------

	

	//cout << "\nЗадание 3\n";

	//
	//vector<long long> vec1 = {2,11,101,1571,16651, 106033, 2124679,16769023,  433494437,1073676287,68718952447, 274876858367,4398042316799,10000000013789,	400000000000763 };
	//vector<long long> vec2 = Rand();
	//vector<long long> vec3 = Less7();
	//
	//
	//ofstream out("results.csv");
	//out << "Size;DataSize;Prime;Random;Less7;\n";
	//size_t size = 512;
	//size_t max_time = 10;

	//bool b1 = true;
	//bool b2 = true;
	//bool b3 = true;

	//for (int i = 0;i < SIZE;i++) {
	//	

	//	out << i+1 << ";" << (i+1) * sizeof(long long) << ";";

	//
	//	if (b1) {
	//		auto t1 = measureFunction("Простые", factorize, vec1, i);
	//		b1 = t1 <= max_time;
	//		out << t1;
	//	}
	//	out << ";";
	//	if (b2) {
	//		auto t2 = measureFunction("Случайные", factorize, vec2, i);
	//		b2 = t2 <= max_time;
	//		out << t2;
	//	}
	//	out << ";";
	//	if (b3) {
	//		auto t3 = measureFunction("С делителями меньше 7", factorize, vec3, i);
	//		b3 = t3 <= max_time;
	//		out << t3;
	//	}
	//	out << "; \n";
	//}
	//out.close();
	//system("results.csv");
	//system("pause");
	//return 0;

	//Task4----------------------------------------------------------------

	cout << "\nЗадание 4\nПереборный алгоритм: " << task4();
	
}