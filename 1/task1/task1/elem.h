#pragma once

#include <iostream>


class elem {
	int value;
public:
	static size_t count_of_comp;
	static size_t count_of_copy;

	elem():value(rand()){}

	elem(const elem& other) : value(other.value) {
		++count_of_copy;
	};

	static void reset() {
		count_of_comp = 0;
		count_of_copy = 0;
	}

	friend std::ostream& operator<<(std::ostream& os, elem& el) {
		return os << el.value << " " << count_of_comp << " " << count_of_copy;
	}

	friend bool operator==(const elem& el1, const elem& el2) {
		++count_of_comp;
		return el1.value == el2.value;
	}

	friend bool operator!=(const elem& el1, const elem& el2) {
		return !(el1 == el2);
	}

	friend bool operator<(const elem& el1, const elem& el2) {
		++count_of_comp;
		return el1.value < el2.value;
	}

	friend bool operator>(const elem& el1, const elem& el2) {
		++count_of_comp;
		return el1.value > el2.value;
	}

	elem& operator=(const elem& el) {
		if (&el == this)
			return *this;
		value = el.value;
		++count_of_copy;
		return *this;
	}
};