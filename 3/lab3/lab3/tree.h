#pragma once



template<typename T> 
struct Node {
	Node* parent;
	T value;
	Node* left;
	Node* right;

	Node(Node* parent, const T& value, Node* left, Node* right)
		: parent(parent), value(value), left(left), right(right){}

	Node(const T& val): parent(nullptr), value(val), left(nullptr), right(nullptr) {}
};

template<typename T>
class Tree {
	Node* root;

public:

	Tree() :root(nullptr){}

	Tree(const Tree& other): root(other.root){}

	Tree(Tree&& other):root(other.root) {
		other.root = nullptr;
	}

	Tree& operator=(const Tree& other) {
		if (this == &right) {
			return *this;
		}
		
		return *this;
	}

	Tree& operator=(Tree&& other) {
		//Todo op=

		return *this;
	}

	//TODO Добавление элемента в дерево;
	public void insert(T value) {
		if (!root)
			root = new Node(value);
	}

	//TODO Поиск элемента;
	public void insert(T value) {

	}

	//TODO Поиск минимального и максимального элементов;
	

	//TODO 4. Поиск первого элемента, больше(меньше) или равного заданного;
	

	//TODO 5. Удаление элемента;
	

	//TODO 6. Вывод на экран – рекурсивный обход(ЛКП);
	

	//TODO 7. Вывод на экран – с использованием стека(ПКЛ) и без использования рекурсии;
	

	//TODO 8. Вывод на экран «по слоям» – с использованием очереди;
	

	//TODO 9. Сравнение двух деревьев на равенство(идентичность полностью, по элементам и структуре, рекурсивно).
	

	//TODO	10.Поиск для заданного(в виде указателя или итератора) элемента следующего и предыдущего элементов
	


};