#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <string>
#include <initializer_list>
#include <exception>
#include <fstream>


int SIZE = 2000;

//from longest to shortest
struct StringLengthComp {
	bool operator()(std::string s1, std::string s2) const{
		return s1.length() < s2.length();
	}
};

template<typename Container>
void print20Max(Container queue) {
	for (int i = 0; i < 20;i++) {
		std::cout << queue.getMax() << " ";
	}
	std::cout << "\n";
}

template<typename Container>
void getWordsFromFile(const std::string& filename, Container& queue) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Unable to open file " << filename << std::endl;
		return;
	}

	std::string word;
	int i = 0;
	while (file >> word && i < SIZE) {
		
		if (!word.empty()) {
			//std::cout << word;
			queue.push(word);
			i++;
		}
	}

	file.close();
}


template<typename T, typename Container = std::vector<T>, typename Compare = std::less<typename Container::value_type>>
class myPriorityQueue1 {
	Container container;
	Compare cmp = Compare();

public:
	myPriorityQueue1(const Container& cont, const Compare& comp):container(cont),cmp(comp){}
	myPriorityQueue1() {
		container = Container();
	}

	myPriorityQueue1(T* arr, size_t size) {
		for (int i = 0; i < size;i++) {
			container.push_back(arr[i]);
		}
		std::sort(container.begin(), container.end(), cmp);
	}

	void push(const T& value) {
		container.push_back(value);
		std::sort(container.begin(), container.end(),cmp);
	}

	void push(std::initializer_list<T> il) {
		for(T x: il)
			container.push_back(x);
		std::sort(container.begin(), container.end(), cmp);
	}

	bool empty() const {
		return size() == 0;
	}

	size_t size() const {
		return container.size();
	}

	void clear() {
		container.clear();
	}


	void println() {
		std::cout << *this << "\n";
	}

	


	T getMax() {
		if (empty())
			throw std::exception("Empty queue");
		T res = container.back();
		container.pop_back();
		return res;
	}

	void merge(const myPriorityQueue1 other) {
		for (T x : other.container) {
			container.push_back(x);
		}
		std::sort(container.begin(), container.end(), cmp);
	}


	friend std::ostream& operator<<(std::ostream& os, const myPriorityQueue1& q) {
		for (T x : q.container) {
			os << x << " ";
		}
		return os;
	}

	
};



//с кучей
template<typename T, typename Container = std::vector<T>, typename Compare = std::less<typename Container::value_type>>
class myPriorityQueue2 {
	Container container;
	Compare cmp = Compare();

public:

	myPriorityQueue2(const Container& cont, const Compare& comp) :container(cont), cmp(comp) {}
	myPriorityQueue2() {
		container = Container();
	}
	myPriorityQueue2(T* arr, size_t size) {
		for (int i = 0; i < size;i++) {
			container.push_back(arr[i]);
		}
		for (int i = size / 2; i >= 0;i--) {
			heapify(i);
		}

	}

private:

	void heapify(unsigned int i) {
		unsigned int left = 2 * i + 1;
		unsigned int right = 2 * i + 2;
		unsigned int largest = i;
		if (left < size() && cmp(container[largest],container[left])) {
			largest = left;
		}
		if (right < size() && cmp(container[largest], container[right])) {
			largest = right;
		}
		if (largest != i) {
			T temp = container[i];
			container[i] = container[largest];
			container[largest] = temp;
			heapify(largest);
		}
	}

public:


	void push(const T& value) {
		container.push_back(value);
		
		unsigned int i = size()-1;
		while (i > 0 && cmp(container[(i-1)/2],container[i]))
		{
			std::swap(container[(i-1) / 2], container[i]);
			
			i = (i-1) / 2;
		}
	}
	bool empty() const {
		return size() == 0;
	}
	size_t size() const {
		return container.size();
	}
	void clear() {
		container.clear();
	}

	void println() {
		std::cout << *this << "\n";
	}

	friend std::ostream& operator<<(std::ostream& os, const myPriorityQueue2& q) {
		for (T x : q.container) {
			os << x << " ";
		}
		return os;
	}

	T getMax() {
		if (empty())
			throw std::exception("Empty queue");
		T mx = container[0];
		container[0] = container[size() - 1];
		container.pop_back();
		heapify(0);
		return mx;
	}

	void merge(const myPriorityQueue2 other) {
		container.insert(container.end(),other.container.begin(), other.container.end());

		for (int i = (size() / 2) - 1; i >= 0; --i) {
			heapify(i);
		}
	}
};
