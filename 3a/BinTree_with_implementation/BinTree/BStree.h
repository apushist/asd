#pragma once

//  Фрагменты для реализации сбалансированных деревьев поиска - заготовка, не рабочая, доделать

#include <iostream>
#include <cassert>
#include <queue>
#include <vector>
#include <string>
#include <iterator>
#include <memory>
#include <memory_resource>
#include <initializer_list>
#include <functional>
#include <exception>
#include <utility>

template<typename T, class Compare = std::less<T>, class Allocator = std::allocator<T>>
class Binary_Search_Tree
{
public:
	//  Объект для сравнения ключей. Должен удовлетворять требованию строго слабого порядка, т.е. иметь свойства:
	//    1. Для любого x => cmp(x,x) == false (антирефлексивность)
	//    2. Если cmp(x,y) == true  =>  cmp(y,x) == false (асимметричность)
	//    3. Если cmp(x,y) == cmp(y,z) == true  =>  cmp(x,z) == true  (транзитивность)
	//    4. Если cmp(x,y) == cmp(y,z) == false  =>  cmp(x,z) == false  (транзитивность несравнимости)
	//  Этим свойством обладает, к примеру, оператор <. Если нужно использовать оператор <= , который не обладает
	//     нужными свойствами, то можно использовать его отрицание и рассматривать дерево как инвертированное от требуемого.
	Compare cmp = Compare();

private:
	//  Узел бинарного дерева, хранит ключ, три указателя и признак nil для обозначения фиктивной вершины
	class Node
	{
	public:  //  Все поля открыты (public), т.к. само определение узла спрятано в private-части дерева
		//  Возможно, добавить поле типа bool для определения того, является ли вершина фиктивной (листом)
		Node* parent;
		Node* left;
		Node* right;
		bool isNil;
		//  Хранимый в узле ключ
		T data;
		Node(T value = T(), Node* p = dummy, Node* l = dummy, Node* r = dummy) : parent(p), data(value), left(l), right(r),isNil(false) {}
	};

	//  Стандартные контейнеры позволяют указать пользовательский аллокатор, который используется для
	//  выделения и освобождения памяти под узлы (реализует замену операций new/delete). К сожалению, есть 
	//  типичная проблема – при создании дерева с ключами типа T параметром шаблона традиционно указывается
	//  std::allocator<T>, который умеет выделять память под T, а нам нужен аллокатор для выделения/освобождения
	//  памяти под Node, т.е. std::allocator<Node>. Поэтому параметр шаблона аллокатора нужно изменить
	//  с T на Node, что и делается ниже. А вообще это одна из самых малополезных возможностей - обычно мы
	//  пользовательские аллокаторы не пишем, это редкость.

	//  Определяем тип аллокатора для Node (Allocator для T нам не подходит)
	using AllocType = typename std::allocator_traits<Allocator>::template rebind_alloc < Node >;
	//  Аллокатор для выделения памяти под объекты Node
	AllocType Alc;
	
	//  Рекурсивное клонирование дерева (не включая фиктивную вершину)
	//  Идея так себе - вроде пользуемся стандартной вставкой, хотя явное клонирование вершин было бы лучше
	void clone(Node * from, Node * other_dummy)
	{
		if (from == other_dummy)
			return;
		//	клонирование через insert? оно же будет переразвешиваться
		// Это ещё и рекурсивный проход в ширину, выраждает дево в список
		insert(from->data);	
		clone(from->right, other_dummy);
		clone(from->left, other_dummy);
	}
public:
	//  Эти типы должен объявлять контейнер - для функциональности
	using key_type = T;
	using key_compare = Compare;
	using value_compare = Compare;
	using value_type = typename T;
	using allocator_type = typename AllocType;
	using size_type = typename size_t;
	using difference_type = typename size_t;
	using pointer = typename T *;
	using const_pointer = typename const pointer;
	using reference = value_type & ;
	using const_reference = const value_type &;
	//using iterator = typename _Mybase::iterator;   //  Не нужно! Явно определили iterator внутри данного класса
	class iterator;   //  Предварительное объявление класса iterator, т.к. он определён ниже
	using const_iterator = iterator;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

private:
	// Указатель на фиктивную вершину
	Node* dummy;


	//  Количесто элементов в дереве
	size_type tree_size = 0;

	// Создание фиктивной вершины - используется только при создании дерева
	inline Node* make_dummy()
	{
		// Выделяем память по размеру узла без конструирования
		dummy = Alc.allocate(1);
		
		//  Все поля, являющиеся указателями на узлы (left, right, parent) инициализируем и обнуляем
		std::allocator_traits<AllocType>::construct(Alc, &(dummy->parent));
		dummy->parent = dummy;

		std::allocator_traits<AllocType>::construct(Alc, &(dummy->left));
		dummy->left = dummy;

		std::allocator_traits<AllocType>::construct(Alc, &(dummy->right));
		dummy->right = dummy;

		std::allocator_traits<AllocType>::construct(Alc, &(dummy->isNil));
		dummy->isNil = true;
		
		//  Возвращаем указатель на созданную вершину
		return dummy;
	}

	// Создание узла дерева 
	template <typename T>
	inline Node* make_node(T&& elem, Node * parent, Node* left, Node* right)
	{
		// Создаём точно так же, как и фиктивную вершину, только для поля данных нужно вызвать конструктор
		Node * new_node = Alc.allocate(1);
		
		//  Все поля, являющиеся указателями на узлы (left, right, parent) инициализируем и обнуляем
		std::allocator_traits<AllocType>::construct(Alc, &(new_node->parent));
		new_node->parent = parent;

		std::allocator_traits<AllocType>::construct(Alc, &(new_node->left));
		new_node->left = left;

		std::allocator_traits<AllocType>::construct(Alc, &(new_node->right));
		new_node->right = right;

		//  Конструируем поле данных
		std::allocator_traits<AllocType>::construct(Alc, &(new_node->data), std::forward<T>(elem));


		std::allocator_traits<AllocType>::construct(Alc, &(new_node->isNil));
		new_node->isNil = false;

		//  Возвращаем указатель на созданную вершину
		return new_node;
	}

	// Удаление фиктивной вершины
	inline void delete_dummy(Node* node) {
		std::allocator_traits<AllocType>::destroy(Alc, &(node->parent));
		std::allocator_traits<AllocType>::destroy(Alc, &(node->left));
		std::allocator_traits<AllocType>::destroy(Alc, &(node->right));
		std::allocator_traits<AllocType>::deallocate(Alc, node, 1);
	}
	
	// Удаление вершины дерева
	inline void delete_node(Node * node) {
		//  Тут удаляем поле данных (вызывается деструктор), а остальное удаляем так же, как и фиктивную
		std::allocator_traits<AllocType>::destroy(Alc, &(node->data));
		delete_dummy(node);
	}

public:
	//  Класс итератора для дерева поиска
	class iterator 
	{
		friend class Binary_Search_Tree;
	protected:
		//  Указатель на узел дерева
		Node* data;

		explicit iterator(Node* d) : data(d) {	}
		
		//  Указатель на узел дерева
		inline Node* &_data()
		{
			return data;
		}

		//  Родительский узел дерева
		inline iterator Parent() const noexcept
		{
			return iterator(data->parent);
		}
		//  Левый дочерний узел (если отсутствует, то фиктивная вершина)
		inline iterator Left() const noexcept
		{
			return data->left->isNil? iterator(dummy) : iterator(data->left);
		}
		//  Правый дочерний узел (если отсутствует, то фиктивная вершина)
		inline iterator Right() const noexcept
		{
			return data->right->isNil ? iterator(dummy) : iterator(data->right);
		}
		//  Является ли узел дерева левым у своего родителя
		inline bool IsLeft() const 
		{
			if(data->parent->isNil)
				throw std::exception("No parent!");
			return data->parent->left == data;
		}
		//  Является ли узел дерева правым у своего родителя
		inline bool IsRight() const 
		{
			if (data->parent->isNil)
				throw std::exception("No parent!");
			return data->parent->right == data;
		}

		
		//  Поиск «самого левого» элемента
		iterator GetMin() {
			Node* node = data;
			while (node->left && node->left->isNil)
				node = node->left;
			return iterator(node);
		}
		//  Поиск «самого правого» элемента
		iterator GetMax() {
			Node* node = data;
			while (node->right && node->right->isNil)
				node = node->right;
			return iterator(node);
		}
	public:


		//  Определяем стандартные типы в соответствии с требованиями стандарта к двунаправленным итераторам
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = Binary_Search_Tree::value_type;
		using difference_type = Binary_Search_Tree::difference_type;
		using pointer = Binary_Search_Tree::pointer;
		using reference = Binary_Search_Tree::reference;

		//  Значение в узле, на который указывает итератор
		inline const T& operator*() const
		{
			return data->data;
		}

		inline bool isNil() const 
		{
			return data->isNil;
		}

	private:
		Node* next(Node* node) {
			Node* cur = node->right;
			if (!cur->isNil)
			{
				while (cur->left)
					cur = cur->left;
			}
			else
			{
				cur = node->parent;
				Compare cmp = Compare();
				while (!cur->isNil && cmp(cur->data, node->data))
					cur = cur->parent;
			}
			return cur;
		}

		Node* previous(Node* node) {
			Node* cur = node->left;
			if (!cur->isNil)
			{
				while (!cur->right->isNil)
					cur = cur->right;
			}
			else
			{
				cur = node->parent;
				Compare cmp = Compare();
				while (!cur->isNil && cmp(node->data, cur->data))
					cur = cur->parent;
			}
			return cur;
		}

	public:

		//  Преинкремент - следующий элемент множества
		iterator & operator++()
		{
			if (isNil())
				throw std::exception("Nil iterator");
			*this =  iterator(next(data));
			return *this;
		}
		//  Предекремент - переход на предыдущий элемент множества
		iterator & operator--()
		{
			if (isNil())
				throw std::exception("Nil iterator");
			*this = iterator(previous(data));
			return *this;
		}
		//  Постинкремент
		iterator operator++(int) {
			if (isNil())
				throw std::exception("Nil iterator");
			iterator temp = *this;
			*this = iterator(next(data));
			return temp;
		}
		//  Постдекремент
		iterator operator--(int) {
			if (isNil())
				throw std::exception("Nil iterator");
			iterator temp = *this;
			*this = iterator(previous(data));
			return temp;
		}

		friend bool operator != (const iterator & it_1, const iterator & it_2)
		{
			return !(it_1 == it_2);
		}

		friend bool operator == (const iterator & it_1, const iterator & it_2)
		{
			return it_1.data == it_2.data;
		}
		
		//  Эти операции не допускаются между прямыми и обратными итераторами
		const iterator & operator=(const reverse_iterator& it) = delete;
		bool operator==(const reverse_iterator& it) = delete;
		bool operator!=(const reverse_iterator& it) = delete;
		iterator(const reverse_iterator& it) = delete;
	};
	
	iterator begin() const noexcept { return iterator(dummy->left);	}
	iterator end() const noexcept { return iterator(dummy);  }

	reverse_iterator rbegin() const	noexcept { return reverse_iterator(iterator(dummy->right)); }
	reverse_iterator rend() const noexcept { return reverse_iterator(iterator(dummy)); }

	Binary_Search_Tree(Compare comparator = Compare(), AllocType alloc = AllocType())
		: dummy(make_dummy()), cmp(comparator), Alc(alloc) {}

	Binary_Search_Tree(std::initializer_list<T> il) : dummy(make_dummy())
	{
		for (const auto &x : il)
			insert(x);
	}

	AllocType get_allocator() const noexcept { return Alc; }
	key_compare key_comp() const noexcept { return cmp; }
	value_compare value_comp() const noexcept { return cmp; }

	inline bool empty() const noexcept { return tree_size == 0; }

private:
	template <class RandomIterator>
	void ordered_insert(RandomIterator first, RandomIterator last, iterator position) {
		if (!(first < last)) return;
		RandomIterator center = first + (last - first)/2 ;
		iterator new_pos = insert(position, *center);  //  итератор на вставленный элемент
		
		ordered_insert(first, center, position);
		
		ordered_insert(center + 1, last, ++position);
	}

public:
	template <class InputIterator>
	Binary_Search_Tree(InputIterator first, InputIterator last, Compare comparator = Compare(), AllocType alloc = AllocType()) : dummy(make_dummy()), cmp(comparator), Alc(alloc)
	{
		//  Проверка - какой вид итераторов нам подали на вход
		if constexpr(std::is_same<typename std::iterator_traits<InputIterator>::iterator_category, typename std::random_access_iterator_tag>::value) {
			//  Если итератор произвольного доступа, то есть надежда, что диапазон отсортирован
			//    а даже если и нет - не важно, всё равно попробуем метод деления пополам для вставки
			
			ordered_insert(first, last, end());
		}
		else
			std::for_each(first, last, [this](T x) { insert(x); });
	}

	Binary_Search_Tree(const Binary_Search_Tree & tree) : dummy(make_dummy())
	{	//  Размер задаём
		tree_size = tree.tree_size;
		if (tree.empty()) return;

		dummy->parent = recur_copy_tree(tree.dummy->parent, tree.dummy);
		dummy->parent->parent = dummy;

		//  Осталось установить min и max
		dummy->left = iterator(dummy->parent).GetMin()._data();
		dummy->right = iterator(dummy->parent).GetMax()._data();
	}

	private:

    //  Рекурсивное копирование дерева
	Node* recur_copy_tree(Node * source, const Node * source_dummy) 
	{
		//  Сначала создаём дочерние поддеревья
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
		
		//  Теперь создаём собственный узел
		Node* current = make_node(source->data, nullptr, left_sub_tree, right_sub_tree);
		//  Устанавливаем родителей
		if (source->right != source_dummy)
			current->right->parent = current;
		if (source->left != source_dummy)
			current->left->parent = current;
		//  Ну и всё, можно возвращать
		return current;
	}

	public:
	const Binary_Search_Tree & operator=(const Binary_Search_Tree &tree)
	{
		if (this == &tree) return *this;
		
		Binary_Search_Tree tmp{tree};
		swap(tmp);
		
		return *this;
	}

	size_type size() const { return tree_size; }

	// Обмен содержимым двух контейнеров
	void swap(Binary_Search_Tree & other) noexcept {
		std::swap(dummy, other.dummy);

		//  Обмен размера множеств
		std::swap(tree_size, other.tree_size);
	}

	//Вставка элемента по значению. 
	std::pair<iterator, bool> insert(const T & value)
	{
		Node* resn = dummy;
		
		if (dummy->parent->isNil)
		{
			resn = make_node(value,dummy,dummy,dummy);
			dummy->parent = resn;
			dummy->left = resn;
			dummy->right = resn;
			tree_size++;
			return std::make_pair(iterator(resn), true);
		}
		Node* node = dummy->parent;
		while (!node->isNil) {
			if (cmp(value,node->data)) {
				if (node->left != dummy)
					node = node->left;
				else
				{
					
					node->left = make_node(value, node, dummy, dummy);
					resn = node->left;
					if (cmp(resn->data,*begin())) {
						dummy->left = resn;
					}
					break;
				}
			}
			else
				if (cmp(value, node->data)) {
					if (node->right != dummy)
						node = node->right;
					else
					{
						node->right = make_node(value, node, dummy, dummy);
						resn = node->right;
						if (cmp(resn->data,*rbegin()))
							dummy->right = resn;
						break;
					}
				}
				else
					break;
		}
		return std::make_pair(iterator(resn), resn->isNil);
	}	

	iterator insert(const_iterator position, const value_type& x) { 
		iterator prev = --position;
		if ((position == begin() || cmp(*prev, x)) && cmp(x, *position)) {
			Node* node = position._data();
			Node* newnode;
			if (!node->left->isNil){
				node = node->left;
				while (!node->right->isNil)
				{
					node = node->right;
				}
			}
			newnode = make_node(x, node, dummy, dummy);
			tree_size++;
			return iterator(newnode);
		}
		throw std::exception("Wrong position");
		
	}

	//  Не самый лучший вариант.
	template <class InputIterator>
	void insert(InputIterator first, InputIterator last) {
		while (first != last) insert(*first++);
	}

	iterator find(const value_type& value) const {
		
		iterator current = iterator(dummy->parent);
		while (!current._data()->isNil)
		{
			if (cmp(value, *current)) {
				if (current.Left().isNil())
					current = current.Left();
				else
					return iterator(dummy);
			}
			else {
				if (!cmp(value, *current)) {
					if (current.Right().isNil())
						current = current.Right();
					else
						return iterator(dummy);
				}
				else {
					return current;
				}
			}
		}
	}

	iterator lower_bound(const value_type& key) {
		iterator current{ dummy->parent }, result{ dummy };
		while (!current._data()->isNil)
		{
			if (!cmp(*current, key)) {
				current = current.Left();
			}
			else {
				result = current;
				current = current.Right();
			}
		}
		
		return result;
	}

	const_iterator lower_bound(const value_type& key) const {
		return const_iterator(const_cast<Binary_Search_Tree *>(this)->lower_bound(key));
	}

	iterator upper_bound(const value_type& key) {
		iterator current{ dummy->parent }, result{ dummy };
		while (!current._data()->isNil)
		{
			if (cmp(*current, key)) {
				current = current.Left();
			}
			else {
				result = current;
				current = current.Right();
			}
		}

		return result;
		
	}

	const_iterator upper_bound(const value_type& key) const {
		return const_iterator(const_cast<Binary_Search_Tree*>(this)->upper_bound(key));
	}

	size_type count(const value_type& key) const {
		return find(key) != end() ? 1 : 0;
	}

	std::pair<const_iterator, const_iterator> equal_range(const value_type& key) const {
		const_iterator it = find(key);
		return std::make_pair(it, it);
	}

protected:
	//  Удаление листа дерева. Возвращает количество удалённых элементов
	size_type delete_leaf(iterator leaf) {
		Node* parent = leaf.Parent()._data();
		if (leaf == begin())
			dummy->left = parent;
		if (leaf == rbegin())
			dummy->right = parent;
		if (leaf.IsLeft()) {
			parent->left = dummy;			
		}
		else {
			parent->right = dummy;
		}
		delete_node(leaf.data);
		return 1;
	}

	//  Меняет местами текущий узел и максимальный в левом поддереве Возвращает тот же итератор, но теперь он без правого поддерева
	iterator replace_with_max_left(iterator node)
	{
		//  Находим максимальный элемент слева. У него нет правого дочернего, и он не может быть корнем или самым правым
		iterator left_max = node.Left().GetMax();
		std::swap(node.data, left_max.data);


		return node;
	} 	

	void setChild(iterator elem, Node* child) {
		Node* node = elem.data;
		Node* parent = elem.Parent()._data();
		child->parent = parent;
		if (!elem.Parent().isNil()) {
			if (elem.IsRight())
				parent->right = child;
			else
				parent->left = child;
		}
		else
			dummy->parent = child;
		delete_node(node);
	}


public:
	//  Удаление элемента, заданного итератором. Возвращает количество удалённых элементов (для set - 0/1)
	size_t erase(iterator elem) {
		//  Если фиктивный элемент, то ошибка - такого не должно происходить
		if (elem.isNil()) 
			throw std::exception("elem is nil!");
		tree_size--;
		if (elem.Left().isNil() && elem.Right().isNil()) {
			delete_leaf(elem);
		}
		else {
			if (elem.Left().isNil()) {
				setChild(elem, elem.Right()._data());
			}
			else {
				if (elem.Right().isNil()) {
					setChild(elem, elem.Left()._data());
				}
				else {
					replace_with_max_left(elem);
					erase(elem);
				}
			}
		}

		return 1;
	}
	
	size_type erase(const value_type& elem) {
		iterator it = find(elem);
		if (it._data()->isNil)
			return 0;
		tree_size--;
		erase(it);
		return 1;
	}
	
	//  Проверить!!!
	iterator erase(const_iterator first, const_iterator last) {
		while (first != last)
		{
			erase(first);
			first++;
		}
		return last;
	}

	//Если передавать по ссылкам,все хорошо. Конструктор копий при нескольких деревьях ломается.
	friend bool operator== (const Binary_Search_Tree &tree_1,
		const Binary_Search_Tree & tree_2)
	{
		auto i = tree_1.begin(), ii = tree_2.begin();
		for (; (i != tree_1.end()) && (ii != tree_2.end()); ++i, ++ii)
		{
			if (*i != *ii)
				return false;
		}
		return i == tree_1.end() && ii == tree_2.end();
	}

	//  Очистка дерева (без удаления фиктивной вершины)
	void clear() {
		Free_nodes(dummy->parent);
		tree_size = 0;
		dummy->parent = dummy->left = dummy->right = dummy;
	}

private:
	//  Рекурсивное удаление узлов дерева, не включая фиктивную вершину
	void Free_nodes(Node* node)
	{ 
		if (node != dummy)
		{
			Free_nodes(node->left);
			Free_nodes(node->right);
			delete_node(node);
		}
	}
	
public:
	~Binary_Search_Tree()
	{
		clear(); // рекурсивный деструктор
		delete_dummy(dummy);
	}
};

template <class Key, class Compare, class Allocator>
void swap(Binary_Search_Tree<Key, Compare, Allocator>& x, Binary_Search_Tree<Key, Compare, Allocator>& y) noexcept(noexcept(x.swap(y))) {
	x.swap(y);
};


template <class Key, class Compare, class Allocator>
bool operator==(const Binary_Search_Tree<Key, Compare, Allocator>& x, const Binary_Search_Tree<Key, Compare, Allocator>& y) {
	typename Binary_Search_Tree<Key, Compare, Allocator>::const_iterator it1{ x.begin() }, it2{ y.begin() };
	while (it1 != x.end() && it2 != y.end() && *it1 == *it2) {
		++it1; ++it2;
	}

	return it1 == x.end() && it2 == y.end();
}

template <class Key, class Compare, class Allocator>
bool operator<(const Binary_Search_Tree<Key, Compare, Allocator>& x, const Binary_Search_Tree<Key, Compare, Allocator>& y) {
	
	typename Binary_Search_Tree<Key, Compare, Allocator>::const_iterator it1{ x.begin() }, it2{ y.begin() };
	while (it1 != x.end() && it2 != y.end() && *it1 == *it2) {
		++it1; ++it2;
	}

	if (it1 == x.end())
		return it2 != y.end();
	
	return it2 != y.end() && *it1 < *it2;
}

template <class Key, class Compare, class Allocator>
bool operator!=(const Binary_Search_Tree<Key, Compare, Allocator>& x, const Binary_Search_Tree<Key, Compare, Allocator>& y) {
	return !(x == y);
}

template <class Key, class Compare, class Allocator>
bool operator>(const Binary_Search_Tree<Key, Compare, Allocator>& x, const Binary_Search_Tree<Key, Compare, Allocator>& y) {
	return y < x;
}

template <class Key, class Compare, class Allocator>
bool operator>=(const Binary_Search_Tree<Key, Compare, Allocator>& x, const Binary_Search_Tree<Key, Compare, Allocator>& y) {
	return !(x<y);
}

template <class Key, class Compare, class Allocator>
bool operator<=(const Binary_Search_Tree<Key, Compare, Allocator>& x, const Binary_Search_Tree<Key, Compare, Allocator>& y) {
	return   !(y < x);
}



