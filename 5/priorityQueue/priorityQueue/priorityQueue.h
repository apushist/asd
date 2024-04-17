#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <string>


template<typename T, typename Container = std::vector<T>, typename Compare = std::less<typename Container::value_type>>
class myPriorityQueue1 {
	Container container;
	Compare cmp = Compare();

public:
	myPriorityQueue1(const Container& cont, const Compare& comp):container(cont),cmp(comp){}
	myPriorityQueue1() {
		container = new Container();
	}

	void push(const T& value) {
		container.push_back(value);
		std::sort(container.begin(), container.end());
	}
	void pop();
	const T& top() const;
	bool empty() const;
	size_t size() const {
		return container.size();
	}
	void clear() {
		container.clear();
	}

};



//с кучей
template<typename T, typename Container = std::vector<T>, typename Compare = std::less<typename Container::value_type>>
class myPriorityQueue2 {
	Container container;
	Compare cmp = Compare();

public:


};
