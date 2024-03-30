
#include <iostream>
#include <iterator>
#include <exception>
#include <initializer_list>


template<typename T, class Compare = std::less<T>>
class AVLTree {

	Compare cmp = Compare();
	size_t tree_size = 0;

	class Node;

	Node* dummy;

	class Node {

	protected:
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

		friend bool operator==(const Node& n1, const Node& n2) {//так как дерево без повторов, можно сравнивать значения
			return cmp(n1.value, n2.value) == 0;
		}
	};
	


public:
	
	class iterator {


		friend class AVLTree;

	private:

		Node* next(Node* node) {
			Node* cur = node->right;
			if (cur->isNil)
			{
				cur = node->parent;
				while (!cur->isNil && cmp(cur->data, node->data))
					cur = cur->parent;
				
			}
			else
			{
				while (cur->left)
					cur = cur->left;
			}
			return cur;
		}

		Node* previous(Node* node) {
			Node* cur = node->left;
			if (cur->isNil)
			{
				cur = node->parent;
				Compare cmp = Compare();
				while (!cur->isNil && cmp(node->data, cur->data))
					cur = cur->parent;				
			}
			else
			{
				while (!cur->right->isNil)
					cur = cur->right;
			}
			return cur;
		}

	protected:

		Node* current;

		bool IsRight() {
			if (current->parent->isNil)
				throw std::exception("No parent!");
			return current->parent->right == current;
		}

		bool IsLeft() {
			if (current->parent->isNil)
				throw std::exception("No parent!");
			return current->parent->left == current;
		}


	public:

		iterator& operator++() {
			if (current->isNil)
				throw std::exception("Nil iterator");
			current = next(current);
			return *this;

		}

		iterator operator++(int) {
			if (current->isNil)
				throw std::exception("Nil iterator");
			iterator temp = *this;
			current = next(current);
			return temp;

		}

		iterator& operator--() {
			if (current->isNil)
				throw std::exception("Nil iterator");
			current = previous(current);
			return *this;
		}

		iterator operator--(int) {
			if (current->isNil)
				throw std::exception("Nil iterator");
			iterator temp = *this;
			current = previous(current);
			return temp;
		}

	};



	size_t size() {
		return tree_size;
	}

	iterator begin() const noexcept { return iterator(dummy->left); }
	iterator end() const noexcept { return iterator(dummy); }


	inline bool empty() const noexcept { return tree_size == 0; }


protected:


	Node* rotateRight(Node* node) {
		if (node->isNil) {
			throw std::exception("Node is nil");
		}

		Node* newNode = node->left;

		node->left = newNode->right;
		newNode->right = node;

		node->fixheight();
		newNode->fixheight();

		if(node == dummy->parent)
			dummy->parent = newNode;

		return newNode;
	}


	Node* rotateLeft(Node* node) {
		if (node->isNil) {
			throw std::exception("Node is nil");
		}

		Node* newNode = node->right;
		node->right = newNode->left;
		newNode->left = node;

		node->fixheight();
		newNode->fixheight();

		if (node == dummy->parent)
			dummy->parent = newNode;

		return newNode;
	}



};