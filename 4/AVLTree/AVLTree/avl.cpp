
#include <iostream>
#include <iterator>
#include <exception>
#include <initializer_list>


template<typename T, class Compare = std::less<T>>
class AVLTree {

	Compare cmp = Compare();

	class Node;

	Node* dummy;

	class Node {
		T value;
		unsigned char height;//-1 0 1
		Node* parent;
		Node* left;
		Node* right;
		bool isNil;
		Node(T val = T(), Node* p = dummy, Node* l = dummy, Node* r = dummy, bool nil = false) : 
			parent(p), value(val), left(l), right(r), isNil(false),height(1) {}


		int bfactor()
		{
			return right->height - left->height;
		}

		void fixheight()
		{
			unsigned char hl = left->height;
			unsigned char hr = right->height;
			height = (hl > hr ? hl : hr) + 1;
		}

		
	};



public:
	
	class iterator {

	};
};