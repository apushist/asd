
#include <iostream>
#include <iterator>
#include <exception>
#include <initializer_list>
#include <stack>
#include <algorithm>
#include <utility>
#include <queue>
#include <fstream>
#include <string>


template<typename T, class Compare = std::less<T>>
class AVLTree {

	Compare cmp = Compare();
	size_t tree_size = 0;
public:

	class Node;

private:

	Node* dummy;
public:

	class Node {

	public:
		T value;
		unsigned char height;
		Node* parent;
		Node* left;
		Node* right;
		bool isNil;

		
		Node() :parent(nullptr), value(T()), left(nullptr), 
			right(nullptr), isNil(false),height(1) {}



		int bfactor()
		{
			return right->height - left->height;
		}

		 void fixheight()
		{
			 if (this == nullptr)
				 return;
			unsigned char hl = left->height;
			unsigned char hr = right->height;
			height = (hl > hr ? hl : hr) + 1;
		}

		friend bool operator==(const Node& n1, const Node& n2) {//так как дерево без повторов, можно сравнивать значения
			return n1.value==n2.value && n1.isNil == n2.isNil;
		}

		friend bool operator!=(const Node& n1, const Node& n2) {
			return !(n1 == n2);
		}

		Node* getMin() {
			Node* res = this;
			if (isNil)
				return res;
			while (!res->left->isNil)
				res = res->left;
			return res;
		}

		Node* getMax() {
			Node* res = this;
			if (isNil)
				return res;
			while (!res->right->isNil)
				res = res->right;
			return res;
		}

		bool isRight() {
			if (parent->isNil)
				return false;
			return parent->right == this;
		}

		bool isLeft() {
			if (parent->isNil)
				return false;
			return parent->left == this;
		}
		
	};
	
private:
	Node* make_node(T val = T(), Node* p = nullptr, Node* l = nullptr, Node* r = nullptr, bool nil = false) {
		Node* res = new Node();
		res->value = val;
		res->parent = p? p: dummy;
		res->left = l? l : dummy;
		res->right = r? r : dummy;
		res->isNil = nil;
		
		return res;
	}

	Node* make_dummy() {
		Node* res = new Node();
		res->value = T();
		res->parent = res->left = res->right = res;
		res->isNil = true;
		res->height = 0;
		return res;
	}


public:


	
	class iterator {


		friend class AVLTree;

	private:

		Compare cmp = Compare();

	

		Node* next(Node* node) {
			Node* cur = node->right;
			if (cur->isNil)
			{
				cur = node->parent;
				while (!cur->isNil && cmp(cur->value, node->value))
					cur = cur->parent;
				
			}
			else
			{
				while (!cur->left->isNil)
					cur = cur->left;
			}
			return cur;
		}

		Node* previous(Node* node) {
			Node* cur = node->left;
			if (cur->isNil)
			{
				cur = node->parent;
				while (!cur->isNil && cmp(node->value, cur->value))
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

		iterator(Node* node):current(node){}

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

		bool isNil() {
			return current->isNil;
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
			if (current->isNil) {
				//current = dummy->parent;
				//current = current->getMax();
			}
			else
				current = previous(current);
			return *this;
		}

		iterator operator--(int) {
				throw std::exception("Nil iterator");
			iterator temp = *this;
			if (current->isNil)
				current = dummy->parent->getMax();
			else
				current = previous(current);
			return temp;
		}

		friend bool operator==(const iterator& it1, const iterator& it2) {
			return it1.current == it2.current;
		}

		friend bool operator!=(const iterator& it1, const iterator& it2) {
			return !(it1 == it2);
		}

		T getValue() {
			return current->value;
		}

		inline const T& operator*() const {
			return current->value;
		}

	};



	size_t size() {
		return tree_size;
	}

	iterator begin() const noexcept { return iterator(dummy->left); }
	iterator end() const noexcept { return iterator(dummy); }


	inline bool empty() const noexcept { return tree_size == 0; }


protected:
	void setParents(Node* node, Node* newNode) {
		
		newNode->parent = node->parent;
		if (node->isLeft()) {
			node->parent->left = newNode;
		}
		if (node->isRight()) {
			node->parent->right = newNode;
		}
		node->parent = newNode;
	}

	Node* rotateRight(Node* node) {
		if (node->isNil) {
			throw std::exception("Node is nil");
		}

		Node* newNode = node->left;

		node->left = newNode->right;
		newNode->right->parent = node;
		newNode->right = node;

		setParents(node, newNode);

		node->fixheight();
		newNode->fixheight();


		return newNode;
	}


	Node* rotateLeft(Node* node) {
		if (node->isNil) {
			throw std::exception("Node is nil");
		}

		Node* newNode = node->right;
		node->right = newNode->left;
		newNode->left->parent = node;
		newNode->left = node;

		setParents(node, newNode);

		node->fixheight();
		newNode->fixheight();


		return newNode;
	}

	unsigned int n = 0;

	iterator balance(iterator it) {
		Node* node = it.current;

		node->fixheight();
		
		if (node->bfactor() == 2) {
			n++;
			if(!node->right->isNil && node->right->bfactor() < 0)
			{
				node->right = rotateRight(node->right);
				n++;
			}
			return iterator(rotateLeft(node));
		}

		if (node->bfactor() == -2) {
			n++;
			if (!node->left->isNil && node->left->bfactor() > 0)
			{
				node->left = rotateLeft(node->left);
				n++;
			}
			return iterator(rotateRight(node));
		}

		return it;
	}

	void fixRoot() {
		Node* root = dummy->parent;
		while (!root->parent->isNil) {
			root = root->parent;
		}
		dummy->parent = root;
	}

	void balanceAll() {
		bah(dummy->parent);
		fixRoot();
	}

	void bah(Node* node) {
		if (node->isNil)
			return;
		bah(node->left);
		bah(node->right);
		balance(node);
	}


public:
	

	
	iterator insert(T value) {
		if (dummy->parent->isNil) { 
			dummy->parent = make_node(value);
			dummy->left = dummy->parent;
			tree_size++;
			return iterator(dummy->parent);
		}

		Node* current = dummy->parent;
		Node* parent = nullptr;

		
		while (!current->isNil) {
			parent->fixheight();
			parent = current;
			if (cmp(value, current->value)) {
				current = current->left;
			}
			else if (cmp(current->value, value)) {
				current = current->right;
			}
			else { 
				return iterator(dummy);
			}
		}

		tree_size++;

		Node* newNode = make_node(value, parent, dummy, dummy);
		if (cmp(value, parent->value)) {
			parent->left = newNode;
		}
		else {
			parent->right = newNode;
		}
		dummy->left = dummy->parent->getMin();
		n = 0;
		balanceAll(); 
		return balance(iterator(newNode));

	
	}

	template <class InputIterator>
	void insert(InputIterator first, InputIterator last) {
		std::for_each(first, last, [this](T x) { insert(x); });
	}

	iterator insert(iterator pos, T value) {
		iterator prev = --pos;
		if ((pos == begin() || cmp(prev.getValue(), value)) && cmp(value, pos.getValue())) {
			Node* node = pos.current;
			
			if (!node->left->isNil) {
				node = node->left;
				while (!node->right->isNil)
				{
					node = node->right;
				}
			}
			Node* newnode = make_node(value, node, dummy, dummy);
			tree_size++;
			return iterator(newnode);
		}
		n = 0;
		balanceAll();
		throw std::exception("Wrong position");
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

		Node* current = make_node(source->value, nullptr, left_sub_tree, right_sub_tree);
		if (source->right != source_dummy)
			current->right->parent = current;
		if (source->left != source_dummy)
			current->left->parent = current;
		return current;
	}

public:

	AVLTree(Compare comparator = Compare()) {
		dummy = make_dummy();
	}
	
	AVLTree(std::initializer_list<T> il) {
		dummy = make_dummy();
		for (T x : il)
			insert(x);
		
	}

	AVLTree(const AVLTree& other) {
		dummy = make_dummy();
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

	iterator find(T value) const {
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

	iterator erase(iterator it) {
		Node* node = it.current;
		iterator res = it++;
		if (node->isNil)
			return iterator(dummy);
		tree_size--;
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
		if (tree_size > 0)
			dummy->left = dummy->parent->getMin();
		else
			dummy->left = dummy;
		n = 0;
		balanceAll();
		return res;
	}

	size_t erase(T value) {
		return erase(find(value)).isNil() ? 0 : 1;
	}

	template <class InputIterator>
	iterator erase(InputIterator first, InputIterator last) {
		iterator res = last++;
		std::for_each(first, last, [this](T x) { erase(x); });
		return res;
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

	friend bool operator==(const AVLTree& tree1, const AVLTree& tree2) {
		Node* r1 = tree1.dummy->parent;
		Node* r2 = tree2.dummy->parent;
		return helpEqual(r1, r2);
	}

private:
	bool static helpEqual(Node* r1, Node* r2) {
		return (!r1->isNil && !r2->isNil) ? (r1->value == r2->value && helpEqual(r1->left, r2->left) && helpEqual(r1->right, r2->right)) : (r1->isNil && r2->isNil);
	}

	void clearHelper(Node* node) {
		if (!node->isNil) {
			clearHelper(node->left); 
			clearHelper(node->right); 
			delete node;
		}
	}
public:

	friend bool operator!=(const AVLTree& t1, const AVLTree& t2) {
		return !(t1 == t2);
	}

	unsigned int getCountOfRotates() {
		return n;
	}

	void clear() {
		clearHelper(dummy->parent);
		dummy->parent = dummy->left = dummy->right = dummy;
		tree_size = 0;
	}

	iterator upper_bound(T value) const {
		Node* res = nullptr;
		Node* cur = dummy->parent;
		while (!cur->isNil)
		{
			if (cmp(value, cur->value)) {
				res = cur;
				cur = cur->left;
			}
			else {
				cur = cur->right;
			}

		}
		return res? iterator(res):iterator(dummy);
	}

	iterator lower_bound(T value) const {
		Node* res = nullptr;
		Node* cur = dummy->parent;
		while (!cur->isNil)
		{
			if (!cmp(value, cur->value)) {
				res = cur;
				cur = cur->right;
			}
			else
				cur = cur->left;
		}
		return res ? iterator(res) : iterator(dummy);
	}

	void printLKP() {
		Node* cur = dummy->parent;
		helpLKP(cur);
		std::cout << "\n";
	}

	void printLevels() {
		Node* cur = dummy->parent;
		std::queue<Node*> q;
		q.push(cur);
		int h = cur->height;
		while (!q.empty()) {
			cur = q.front();
			q.pop();
			
			std::cout << cur->value << " ";
			
			if (!cur->left->isNil)
				q.push(cur->left);
			if (!cur->right->isNil)
				q.push(cur->right);

		}
		std::cout << "\n";

	}


	void saveInFile(std::string filename) {
		std::ofstream out(filename);     
		if (out.is_open())
		{
			std::string str = getString();
			std::cout << str;
			out << str;
		}
		out.close();

	}

private:

	std::string getString() {
		std::string res = "";
		Node* cur = dummy->parent;
		std::queue<Node*> q;
		q.push(cur);
		int h = cur->height;
		while (!q.empty()) {
			cur = q.front();
			q.pop();

			res.append(std::to_string(cur->value) + " ");
			
			if (!cur->left->isNil)
				q.push(cur->left);
			if (!cur->right->isNil)
				q.push(cur->right);

		}
		return res;
	}

	void helpLKP(Node* node) {
		if (node->isNil)
			return;
		helpLKP(node->left);
		std::cout << node->value << " ";
		helpLKP(node->right);
	}

public:

	Compare key_comp() const noexcept { return cmp; }
	Compare value_comp() const noexcept { return cmp; }

	~AVLTree() {
		clear();
		delete dummy;
	}
};

template<typename T, class Compare = std::less<T>, class Allocator = std::allocator<T>>
class mySet {
	AVLTree<T, Compare>* tree;

	using AllocType = typename std::allocator_traits<Allocator>::template rebind_alloc < AVLTree<T, Compare>::Node >;
	
	AllocType Alc;

	Compare cmp = Compare();

public:

	using iterator = typename AVLTree<T, Compare>::iterator;
	using const_iterator = iterator;

	mySet(Compare comparator = Compare(), AllocType alc = AllocType()) {
		tree = new AVLTree<T, Compare>(comparator);
		Alc = alc;
		cmp = comparator;
	}

	mySet(const mySet& other) {
		tree = other.tree;
	}

	mySet(mySet&& other) {
		tree = other.tree;
		delete other.tree;
	}

	mySet(std::initializer_list<T> il) {
		tree = new AVLTree<T, Compare>(il);
	}

	template <class InputIterator>
	mySet(InputIterator first, InputIterator last, Compare comparator = Compare(), AllocType alloc = AllocType()) {
		tree = new AVLTree<T, Compare>(comparator);
		tree->insert(first, last);
		Alc = alloc;
		cmp = comparator;
	}

	const mySet& operator=(const mySet& other) {
		if (this == &other) return *this;

		mySet tmp{ other };
		swap(tmp);

		return *this;
	}

	AllocType get_allocator() {
		return Alc;
	}

	size_t size() {
		return tree->size();
	}

	bool empty() {
		return tree->empty();
	}

	iterator begin() const noexcept { return tree->begin(); }
	iterator end() const noexcept { return tree->end(); }

	void clear() {
		tree->clear();
	}

	void swap(mySet& other)  {
		tree->swap(*other.tree);
	}

	template <class InputIterator>
	void insert(InputIterator first, InputIterator last) {
		tree->insert(first, last);
	}

	std::pair<iterator,bool> insert(T value) {
		iterator res = tree->insert(value);
		return std::make_pair(res,!res.isNil());
	}

	iterator insert(iterator pos,T value) {
		return tree->insert(pos, value);
	}

	iterator erase(iterator it) {
		return tree->erase( it);
	}

	size_t erase(T value) {
		return tree->erase(value);
	}

	template <class InputIterator>
	iterator erase(InputIterator first, InputIterator last) {
		return tree->erase(first, last);
	}

	friend bool operator==(const mySet& s1, const mySet& s2) {
		return s1.tree == s2.tree;
	}

	friend bool operator!=(const mySet& s1, const mySet& s2) {
		return !(s1 == s2);
	}

	Compare key_comp() const noexcept { return cmp; }
	Compare value_comp() const noexcept { return cmp; }

	size_t count(T key) const {
		return tree->find(key).isNil() ? 0 : 1;
	}

	iterator lower_bound(T value) const {
		return tree->lower_bound(value);
	}

	iterator upper_bound(T value) const {
		return tree->upper_bound(value);
	}

	iterator find(T value) const {
		return tree->find(value);
	}

	std::pair<const_iterator, const_iterator> equal_range(const T& key) const {
		const_iterator res = tree->find(key);
		return std::make_pair(res++,res);
	}

	void printSideView() {
		tree->printLevels();
	}
};