#pragma once

#include "tree.h"
#include <vector>

template<typename T>
class MySet {
	Tree<T>* t;

public:
	MySet() {
		t = new Tree<T>();
	}
	
	void print() {
		t->printLKP();
	}

	//Todo 1. Добавление/удаление элемента;
	void add(T value) {
		t->insert(value);
	}

	void deleteElem(T value) {
		t->deleteElem(value);
	}

	
	//todo 2. Проверка на вхождение элемента
	bool contains(T value) {
		return t->find(value) != nullptr;
	}
};


//Sieve of Eratosthenes set
MySet<int> Sieve_of_Eratosthenes_set(int n) {
	MySet<int> res;
	for (int i = 2; i <= n;i++) {
		res.add(i);
	}
	for (int j = 2; j*j <= n; ++j) {
		if (res.contains(j)) {
			for (int k = j * j; k <= n; k += j) {
				res.deleteElem(k);
			}
		}
	}
	return res;
}

//Sieve of Eratosthenes vector
std::vector<int> Sieve_of_Eratosthenes_vector(int n) {
	std::vector<int> res;
	int* temp = new int[n + 1];

	for (int i = 0; i < n + 1; i++)
		temp[i] = i;
	for (int j = 2; j < n; ++j) {
		int x = temp[j];
		if (x != 0) {
			res.push_back(x);
			for (int k = j * j; k <= n; k += j) {
				temp[k] = 0;
			}
		}
	}
	return res;
}