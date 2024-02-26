
// Сравниваем время работы разных реализаций алгоритмов на примере перемножения элементов вектора

#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <vector>
#include <algorithm>
#include <iterator>
#include <random>
#include <chrono>
#include <valarray>
#include <string>
#include <fstream>
#include <cmath>
#include <omp.h>

#include <intrin.h>
#pragma intrinsic(__rdtsc)

typedef float elem_type;
const size_t iterations(100);

//  Перемножение "в лоб"
template<typename RandIt>
elem_type combine0(RandIt begin, RandIt end)
{
	elem_type dest(1);
	for (; begin != end; ++begin)
		dest *= *begin;
	return dest;
}

//  Магия
template<typename RandIt>
elem_type combine4(RandIt begin, RandIt end)
{
	elem_type acc0(1), acc1(1), acc2(1), acc3(1);
	
	RandIt it = begin;
	RandIt finish = end - 4;
	for (; it < finish; it += 4) {
		acc0 *= *it;
		acc1 *= *(it + 1);
		acc2 *= *(it + 2);
		acc3 *= *(it + 3);
	}
	while (it != end) acc0 *= *it++;
	return acc0 * acc1 * acc2 * acc3;
}

//  Параллельная магия
template<typename RandIt>
elem_type combine5(RandIt begin, RandIt end)
{
	const size_t threads = 4;
	std::valarray<elem_type> acc(1,threads);
	
	size_t size(end - begin);
	size_t block_size = size / threads;
	if (block_size < threads)
		throw("Not enought elements for correct work!");
	size_t tail = size - size % threads;
	
	omp_set_num_threads(4);
	#pragma omp parallel
	{
		#pragma omp for
		for (int block = 0; block < threads; ++block) {
			RandIt it = begin + block * block_size;
			RandIt finish = it + block_size - 4;
			elem_type acc0(1), acc1(1), acc2(1), acc3(1);
			for (; it < finish; it += 4) {
				acc0 *= *it;
				acc1 *= *(it + 1);
				acc2 *= *(it + 2);
				acc3 *= *(it + 3);
			}
			finish = begin + (block + 1) * block_size;
			while (it != finish) acc0 *= *it++;
			acc[block] = acc0*acc1*acc2*acc3;
		}
	}

	size_t diff = size - size % threads;
	for (RandIt it = begin + (size - size % threads); it!=end; ++it) acc[0] *= *it;
	for (size_t i = 1; i < threads; ++i) acc[0] *= acc[i];

	return acc[0];
}

//  Шаблон функции-измерителя, предназначенной для измерения времени и тиков процессора
template<typename Func, typename RandIt>
double measureFunction(std::string name, Func f, RandIt begin, RandIt end) {
	
	using namespace std;
	using namespace std::chrono;

	cout << "Starting alg " << name << "..." << endl;
	
	//  Запускаем таймер
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	
	//  Запоминаем текущее количество тиков процессора
	unsigned __int64 ticks = __rdtsc();

	//  Прогоняем алгоритм несколько раз
	elem_type result(1);
	for (int i = 0; i < iterations; ++i)
		result *= f(begin, end);
	
	//  Считываем затраченные тики
	ticks = __rdtsc() - ticks;

	//  Снимаем показания таймера
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration<double> time_span1 = duration_cast<chrono::nanoseconds>(t2 - t1);

	//  Отчитываемся
	cout << "It took me " << time_span1.count() << " seconds.\n";
	cout << "It took me " << ticks << " ticks.\n";
	double cpe = double(ticks) / (end - begin) / iterations;
	cout << "CPE : " << cpe  << "\n";
	cout << "Result : " << result << "\n";
	cout << "_________________________________________________\n";
	
	//  Возвращаем количество тиков
	return cpe;
}

int main() {
	
	using namespace std;
	using namespace std::chrono;
	
	//  Создаём генератор случайных чисел
	random_device rd;
	mt19937 engine(rd());
	uniform_int_distribution<int> dist(1, 100);
	
	//  Генерируем случайный вектор
	const size_t SIZE = 30000000;
	vector<elem_type> vec;
	vec.reserve(SIZE);
	generate_n(back_insert_iterator<vector<elem_type>>(vec), SIZE, [&]() { return elem_type(dist(engine))/40; });
	
	ofstream out("results.csv");
	out << "Size;DataSize;Alg1;Alg2;Alg3;\n";
	size_t size = 512;
	for (; size <= SIZE; size = size_t(size*1.3)) {
		//  Измеряем время работы различных алгоритмов
		auto t1 = measureFunction("Combine_0", combine0<vector<elem_type>::iterator>, vec.begin(), vec.begin() + size);
		auto t2 = measureFunction("Combine_4", combine4<vector<elem_type>::iterator>, vec.begin(), vec.begin() + size);
		auto t3 = measureFunction("Combine_5", combine5<vector<elem_type>::iterator>, vec.begin(), vec.begin() + size);
		out << size << ";" << size * sizeof(elem_type) << ";" << t1 << "; " << t2 << "; " << t3 << "; \n";
	}
	out.close();
	system("results.csv");
	system("pause");
	return 0;
}

