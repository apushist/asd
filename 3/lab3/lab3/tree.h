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

	//TODO ���������� �������� � ������;
	public void insert(T value) {
		if (!root)
			root = new Node(value);
	}

	//TODO ����� ��������;
	public void insert(T value) {

	}

	//TODO ����� ������������ � ������������� ���������;
	

	//TODO 4. ����� ������� ��������, ������(������) ��� ������� ���������;
	

	//TODO 5. �������� ��������;
	

	//TODO 6. ����� �� ����� � ����������� �����(���);
	

	//TODO 7. ����� �� ����� � � �������������� �����(���) � ��� ������������� ��������;
	

	//TODO 8. ����� �� ����� ��� ����� � � �������������� �������;
	

	//TODO 9. ��������� ���� �������� �� ���������(������������ ���������, �� ��������� � ���������, ����������).
	

	//TODO	10.����� ��� ���������(� ���� ��������� ��� ���������) �������� ���������� � ����������� ���������
	


};