#pragma once
#include <iostream>
#include <stack>
#include <queue>


template<typename T>
class Tree {

public:
	struct Node {
		Node* parent;
		T value;
		Node* left;
		Node* right;

		Node(Node* parent, const T& value, Node* left = nullptr, Node* right = nullptr)
			: parent(parent), value(value), left(left), right(right) {}

		Node(const T& val) : parent(nullptr), value(val), left(nullptr), right(nullptr) {}

		friend std::ostream& operator<<(std::ostream& os,Node& n) {
			return os << n.value;
		}


	};
private:
	Node* root;

public:

	Tree() :root(nullptr){}

	Tree(const Tree& other): root(other.root){}

	Tree(Tree&& other):root(other.root) {
		other.root = nullptr;
	}


	void insert(T value) {
		if (!root)
		{
			root = new Node(value);
			return;
		}
		Node* node = root;
		while (node) {
			if (value < node->value) {
				if (node->left)
					node = node->left;
				else
				{
					node->left = new Node(node, value);
					break;
				}
			}
			else
				if (value > node->value) {
					if (node->right)
						node = node->right;
					else
					{
						node->right = new Node(node,value);
						break;
					}
				}
				else
					break;
		}
	}


	Node* find(T value) {
		Node* node = root;
		while (node) {
			if (value < node->value) {
				if (node->left)
					node = node->left;
				else
				{
					return nullptr;
				}
			}
			else
				if (value > node->value) {
					if (node->right)
						node = node->right;
					else
					{
						return nullptr;
					}
				}
				else{
					return node;
				}
		}
	}


	Node* findMax() {
		Node* node = root;
		while (node->right)
			node = node->right;
		return node;
	}

	Node* findMin() {
		Node* node = root;
		while (node->left)
			node = node->left;
		return node;
	}


	Node* upperBound(T value) {
		Node* res = nullptr;
		Node* cur = root;
		while (cur)
		{
			if (cur->value >= value) {
				res = cur;
				cur = cur->left;
			}
			else {
				cur = cur->right;
			}
			
		}
		return res;
	}

	Node* lowerBound(T value) {
		Node* res = nullptr;
		Node* cur = root;
		while (cur)
		{
			if (cur->value <= value) {
				res = cur;
				cur = cur->right;
			}
			else
				cur = cur->left;
		}
		return res;
	}


	void deleteElem(T value) {
		Node* node = find(value);
		if (!node)
			return;
		Node* parent = node->parent;
		if (!node->right) {
			setChild(parent, node, node->left);
			
		}
		else {
			if (!node->left && node->right) {
				setChild(parent, node, node->right);
			}
			else {
				Node* change = node->left;
				while (change->right)
					change = change->right;
				std::swap(node->value, change->value);
				if (change->right)
					setChild(change->parent, change, change->right);
				else
					setChild(change->parent, change, change->left);
			}
		}
	}

private:
	void setChild(Node* parent, Node* node, Node* child) {
		if(child)
			child->parent = parent;
		if (parent) {
			if (parent->right == node)
				parent->right = child;
			else
				parent->left = child;
		}
		else
			root = child;
		delete node;
	}
public:


	void printLKP() {
		Node* cur = root;
		helpLKP(cur);
		std::cout << "\n";
	}

private:

	void helpLKP(Node* node)  {
		if (!node)
			return;
		helpLKP(node->left);
		std::cout << *node << " ";
		helpLKP(node->right);
	}
public:

	void printPKL() {
		Node* cur = root;

		std::stack<Node*> st;

		while (cur || !st.empty())
		{
			while (cur)
			{
				st.push(cur);
				cur = cur->right;
			}

			cur = st.top();
			st.pop();
			std::cout << *cur << " ";
			cur = cur->left;
		}
		std::cout << "\n";

	}

private:

		void setMin(Node* node) {
			while (node->left)
				node = node->left;
		}
public:
	

	void printLevels() {
		Node* cur = root;
		std::queue<Node*> q;
		q.push(cur);
		while (!q.empty()) {
			cur = q.front();
			q.pop();
			std::cout << *cur << " ";
			if (cur->left)
				q.push(cur->left);
			if (cur->right)
				q.push(cur->right);

		}
		std::cout << "\n";

	}
	

	bool operator==(Tree& tree) {
		Node* r1 = root;
		Node* r2 = tree.root;
		return helpEqual(r1, r2);
	}

private:
	bool helpEqual(Node* r1, Node* r2) {
		return (r1 && r2) ? (r1->value == r2->value && helpEqual(r1->left, r2->left) && helpEqual(r1->right, r2->right)): (!r1 &&!r2);
	}
public:

	Node* next(Node* node) {
		if (!node)
			return nullptr;
		Node* cur = node->right;
		if(cur)
		{
			while (cur->left)
				cur = cur->left;
		}
		else
		{
			T value = node->value;
			cur = node->parent;
			while (cur && value > cur->value)
				cur = cur->parent;
		}
		return cur;
	}

	Node* previous(Node* node) {
		if (!node)
			return nullptr;
		Node* cur = node->left;
		if (cur)
		{
			while (cur->right)
				cur = cur->right;
		}
		else
		{
			T value = node->value;
			cur = node->parent;
			while (cur && value < cur->value)
				cur = cur->parent;
		}
		return cur;
	}


};
