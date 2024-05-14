#pragma once
#include <vector>
#include <iostream>



class HashTable {

	class Node {
	public:
		int value;

		bool deleted;

		Node(int val,bool del = false):value(val),deleted(del){}

		bool friend operator==(const Node& n1, const Node& n2) {
			return n1.value == n2.value && n1.deleted == n2.deleted;
		}

		bool friend operator!=(const Node& n1, const Node& n2) {
			return !(n1 == n2);
		}

		
	};

	std::vector<std::vector<Node>> container;
	size_t size;
	size_t elem_count;
	size_t deleted_count;

	size_t hashFunction(int value) const {
		return value % size;
	}

	void rehash() {
		std::vector<std::vector<Node>> new_container(size);
		for (int i = 0; i < size;i++) {
			for (Node x : container[i]) {
				if(!x.deleted)
					new_container[i].push_back(Node(x.value));
			}
		}
		container = new_container;
		
		elem_count -= deleted_count;
		deleted_count = 0;
	}


public:
	HashTable(size_t capacity) : size(capacity),deleted_count(0) {
		container.resize(size);
	}

	void insert(int value) {
		container[hashFunction(value)].push_back(Node(value));
		elem_count++;
	}

	void remove(int value) {
		std::vector<Node>& vect = container[hashFunction(value)];
		auto pos = std::find(vect.begin(), vect.end(), value);
		while (pos != vect.end())
		{
			pos->deleted = true;
			deleted_count++;
			if (pos != vect.end() && pos + 1 != vect.end())
				pos = std::find(pos + 1, vect.end(), value);
			else
				pos = vect.end();
		}
		if (deleted_count >= (elem_count / 2+1)) {
			rehash();
		}
	}

	bool contains(int value) {
		std::vector<Node> vect = container[hashFunction(value)];
		return std::find(vect.begin(), vect.end(), value) != vect.end();
	}

	friend std::ostream& operator<< (std::ostream& os, const HashTable& ht)
	{
		for (int i = 0; i < ht.size;i++) {
			std::vector<Node> vect_i = ht.container[i];
			os << "Hash " << i << ": ";
			for (int j = 0;j < vect_i.size();j++) {
				if (vect_i[j].deleted) {
					os << " [empty] ";
				}
				else {
					int val = vect_i[j].value;
					os << " [ind: " << j << ", value: " << val << "] ";
				}
			}
			os << "\n";
		}
		return os;
	}
};