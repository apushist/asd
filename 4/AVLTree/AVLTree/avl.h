
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

	public:
		T value;
		unsigned char height;//-1 0 1
		Node* parent;
		Node* left;
		Node* right;
		bool isNil;
		Node(T val = T(), Node* p = nullptr, Node* l = nullptr, Node* r = nullptr, bool nil = false) :
			parent(p), value(val), left(l), right(r), isNil(false),height(1) {
			make_node(p, l, r);
		}



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
			return n1.value==n2.value;
		}

		friend bool operator!=(const Node& n1, const Node& n2) {
			return !(n1 == n2);
		}

		Node* getMin() {
			Node* res = this;
			while (res->left->isNil)
				res = res->left;
			return res;
		}

		Node* getMax() {
			Node* res = this;
			while (res->right->isNil)
				res = res->right;
			return res;
		}

	private:

		void make_node(Node* p, Node* l, Node* r) {

			if (!p)
				parent = dummy;
			if (!l)
				left = dummy;
			if (!r)
				right = dummy;
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

	public:

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

		friend bool operator==(const iterator& it1, const iterator& it2) {
			return it1.current == it2.current;
		}

		friend bool operator!=(const iterator& it1, const iterator& it2) {
			return !(it1 == it2);
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

	iterator balance(iterator it) {
		Node* node = it.current;
		node->fixheight();
		if (node->bfactor() == 2) {
			if(!node->right->isNil && node->right->bfactor() < 0)
				node->right = rotateRight(node->right);
			return iterator(rotateLeft(node));
		}

		if (node->bfactor() == -2) {
			if (!node->left->isNil && node->left->bfactor() > 0)
				node->left = rotateLeft(node->left);
			return iterator(rotateRight(node));
		}

		return it;

	}

	void balanceAll() {
		
		iterator current = begin();
		while (current != end())
		{
			current = balance(current++);
		}
	}


public:
	
	iterator insert(T value) {
		Node* node = new Node(value);
		if (dummy->parent->isNil) {
			dummy->parent = node;
			dummy->left = node;
			tree_size++;
			return iterator(node);
		}
		Node* cur = dummy->parent;
		while (true) {
			if (cmp(value, cur->value)) {
				if (cur->left->isNil) {
					node->parent = cur;
					cur->left = node;
					break;

				}
				else {
					cur = cur->left;
				}
			}
			else {
				if (cmp(cur->value, value)) {
					if (cur->right->isNil) {
						node->parent = cur;
						cur->right = node;
						
						break;

					}
					else {
						cur = cur->right;
					}
				}
				else {
					return iterator(dummy);
				}
			}
		}
		tree_size++;
		balanceAll();
		return iterator(node);
	}

private:
	Node* recur_copy_tree(Node* source, const Node* source_dummy)
	{
		Node* left_sub_tree;
		if (source->left != source_dummy)
			left_sub_tree = recur_copy_tree(source->left, source_dummy);
		else
			left_sub_tree = dummy;

		Node* right_sub_tree;
		if (source->right != source_dummy)
			right_sub_tree = recur_copy_tree(source->right, source_dummy);
		else
			right_sub_tree = dummy;

		Node* current = new Node(source->value, nullptr, left_sub_tree, right_sub_tree);
		if (source->right != source_dummy)
			current->right->parent = current;
		if (source->left != source_dummy)
			current->left->parent = current;
		return current;
	}

public:

	AVLTree(Compare comparator = Compare()) {
		dummy = new Node(T());
		dummy->isNil = true;
	}
	
	AVLTree(std::initializer_list<T> il) {
		dummy = new Node(T());
		dummy->isNil = true;
		for (T x : il)
			insert(x);
	}

	AVLTree(const AVLTree& other) {
		tree_size = other.tree_size;
		if (other.empty())
			return;

		dummy->parent = recur_copy_tree(other.dummy->parent, other.dummy);
		dummy->parent->parent = dummy;

		dummy->left = dummy->parent->getMin();
	}

	AVLTree(AVLTree&& other) {
		dummy = other.dummy;
		tree_size = other.tree_size;
		other.clear();
		delete other.dummy;
	}
	

	const AVLTree& operator=(const AVLTree& tree) {
		if (this == &tree) return *this;

		AVLTree tmp{ tree };
		swap(tmp);

		return *this;
	}

	void swap(AVLTree& other) noexcept {
		std::swap(dummy, other.dummy);
		std::swap(tree_size, other.tree_size);
	}

	iterator find(T value) {
		Node* cur = dummy->parent;
		while (!cur->isNil) {
			if (cmp(value, cur->value)) {
				cur = cur->left;
			}
			else {
				if (cmp(cur->value, value)) {
					cur = cur->right;
				}
				else {
					return iterator(cur);
				}
			}
		}
		return iterator(dummy);
	}

	void erase(T value) {
		Node* node = find(value).current;
		if (node->isNil)
			return;
		Node* parent = node->parent;
		if (node->right->isNil) {
			deleteElem(parent, node, node->left);

		}
		else {
			if (node->left->isNil) {
				deleteElem(parent, node, node->right);
			}
			else {
				Node* change = node->left;
				while (!change->right->isNil)
					change = change->right;
				std::swap(node->value, change->value);
				if (change->right->isNil)
					deleteElem(change->parent, change, change->left);
				else
					deleteElem(change->parent, change, change->right);
			}
		}
		dummy->left = dummy->parent->getMin();
		balanceAll();

	}

private:
	void deleteElem(Node* parent, Node* node, Node* child) {
		if (!child->isNil)
			child->parent = parent;
		if (!parent->isNil) {
			if (parent->right == node)
				parent->right = child;
			else
				parent->left = child;
		}
		else
			dummy->parent = child;
		delete node;
	}

public:

	friend bool operator==(const AVLTree& t1, const AVLTree& t2) {
		iterator it1 = t1.begin();
		iterator it2 = t2.begin();
		for (;it1 != t1.end() && it2 != t2.end();++it1, ++it2) {
			if (it1.current != it2.current) {
				return false;
			}

		}
		return it1 == t1.end() && it2 == t2.end();
	}

	friend bool operator!=(const AVLTree& t1, const AVLTree& t2) {
		return !(t1 == t2);
	}

	void clear() {
		iterator cur = begin();
		for (;cur != end();++cur) {
			erase(cur.current->value);
			tree_size = 0;
			dummy->parent = dummy->left = dummy->right = dummy;
		}
	}


	Compare key_comp() const noexcept { return cmp; }
	Compare value_comp() const noexcept { return cmp; }

	~AVLTree() {
		clear();
	}
};