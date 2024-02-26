#pragma once

#include <algorithm>
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <vector>
#include <iterator>
#include <random>
#include <chrono>
#include <valarray>
#include <string>
#include <fstream>
#include <cmath>
#include <omp.h>

#include <intrin.h>


typedef float elem_type;
const size_t iterations(5000);
const size_t SIZE = 15;

//�������� ��������, ����������� ������������ �����. 
std::vector<long long> factorize(long long x) {
	std::vector<long long> factors;

	for (long long i = 2; i <= sqrt(x); i++) {
		while (x % i == 0) {
			factors.push_back(i);
			x /= i;
		}
	}

	if (x != 1) {
		factors.push_back(x);
	}

	return factors;
}



std::vector<long long> Rand() {
	std::vector<long long> v;
	std::random_device rd;
	std::mt19937 engine(rd());
	long long a = 1;
	for (int i = 0; i < SIZE; i++) {
		std::uniform_int_distribution<long long> dist(a, a*10);

		v.push_back(dist(engine));

		a *= 10;
	}
	return v;
}

//�����, ��� ������� �������� �� ����������� 7.
std::vector<long long> Less7() {
	std::vector<long long> v;
	long long l = 1;
	long long x = 2;
	std::vector<int> mn = { 2,3,5 };
	
	for (int i = 0; i < SIZE; i++) {
		
		while (x < l)
			x *= mn[rand()%3];
		v.push_back(x);
		l *= 10;
	}
	return v;
}





//  ������ �������-����������, ��������������� ��� ��������� ������� � ����� ����������
template<typename Func>
double measureFunction(std::string name, Func f, std::vector<long long> v, int i) {

	using namespace std;
	using namespace std::chrono;

	cout << "�������� ������ " << name << "..." << endl;

	//  ��������� ������
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	//  ���������� ������� ���������� ����� ����������
	unsigned __int64 ticks = __rdtsc();

	for(int j = 0;j< iterations;j++)
		std::vector<long long> result = f(v[i]);

	//  ��������� ����������� ����
	ticks = __rdtsc() - ticks;

	//  ������� ��������� �������
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration<double> time_span1 = duration_cast<chrono::nanoseconds>(t2 - t1);

	//  ������������
	cout << "��������� " << time_span1.count() << " ������.\n";
	cout << "��������� " << ticks << " �����.\n";
	cout << "____________________________________________________________\n";

	return time_span1.count();
}