#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <string>
#include <initializer_list>
#include <exception>


//from longest to shortest
struct StringLengthComp {
	bool operator()(std::string s1, std::string s2) const{
		return s1.length() < s2.length();
	}
};


template<typename T, typename Container = std::vector<T>, typename Compare = std::less<typename Container::value_type>>
class myPriorityQueue1 {
	Container container;
	Compare cmp = Compare();

public:
	myPriorityQueue1(const Container& cont, const Compare& comp):container(cont),cmp(comp){}
	myPriorityQueue1() {
		container = Container();
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

	void pushFromArray(T* arr, size_t size) {
		for (int i = 0; i < size;i++) {
			container.push_back(arr[i]);
		}
		std::sort(container.begin(), container.end(), cmp);
	}


	T getMax() {
		if (empty())
			throw std::exception("Empty queue");
		return container.back();
	}

	void merge(const myPriorityQueue1 other) {
		for (T x : other.container) {
			container.push_back(x);
		}
		std::sort(container.begin(), container.end(), cmp);
	}


	friend std::ostream& operator<<(std::ostream& os, const myPriorityQueue1& q) {
		for (T x : container) {
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
		container = new Container();
	}

	void push(const T& value) {//todo
		//container.push_back(value);
		//std::sort(container.begin(), container.end(),cmp);


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

	friend std::ostream& operator<<(std::ostream& os, const myPriorityQueue1& q) {
		for (T x : container) {
			os << x << " ";
		}
		return os;
	}
};
