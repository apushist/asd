
#include <iostream>
#include <iterator>


template<typename T, class Compare = std::less<T>>
class AVLTree {

	Compare cmp = Compare();

	class Node;

	Node* dummy;

	class Node {
		T value;
		unsigned char height;
		Node* parent;
		Node* left;
		Node* right;
		bool isNil
		Node(int v):value(v), left(dummy),right(dummy), parent(dummy),height(1), isNil({}

		unsigned char height()
		{
			return isNil ? 0: height ;
		}

		int bfactor()
		{
			return height(right) - height(left);
		}

		void fixheight()
		{
			unsigned char hl = height(left);
			unsigned char hr = height(right);
			height = (hl > hr ? hl : hr) + 1;
		}
	};

public:
	



};