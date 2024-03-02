#include <initializer_list>
#include <memory>
#include <iterator>
#include <exception>
#include <iostream>
#include <functional>
#include <tuple>


template<typename T>
class MyList
{
public:
    using value_type = T;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;


private:
    struct Node
    {
        Node* next;
        Node* prev;
        T data;

        Node(const T& d, Node* p, Node* n) : data(d), prev(p), next(n) {}

        Node(T&& d) : data(std::move(d)) {}

    };
    Node* first;
    Node* last;
    size_t _size;

public:
     template<typename Pointer, typename Reference>
     class BaseIterator : public std::iterator<std::bidirectional_iterator_tag, value_type, difference_type, Pointer, Reference>
     {
        Node* current;
     private:
        explicit BaseIterator(Node* ptr) :current(ptr) {}
        BaseIterator() : current(T(), nullptr, nullptr) {}

        friend class MyList;

     public:
         
         Node* getCurrent() {
             return current;
         }
        
         bool operator==(const BaseIterator& other) {
             return current == other.current;
         }
         bool operator!=(const BaseIterator& other) {
                 return !(*this == other);
         }
         pointer operator->() {
            return *(current->data);
         }
         BaseIterator& operator--() {
             if (current == nullptr)
                 throw std::exception();
             current = current->prev;
             return *this;
         }
         BaseIterator operator--(int) {
            if (current == nullptr)
                throw std::exception();
            BaseIterator t(*this);
            current = current->prev;
            return t;
         }
         BaseIterator& operator++() {
            if (current == nullptr)
               throw std::exception();
            current = current->next;
            return *this;
         }
         BaseIterator operator++(int) {
            if (current == nullptr)
                throw std::exception();
            BaseIterator t(*this);

            current = current->next;
            return t;
         }
         
         Reference operator*() {
             if (current == nullptr)
                    throw std::exception();
                return current->data;
         }
     };
     
     using iterator = BaseIterator<pointer, reference>;
     using const_iterator = BaseIterator<const_pointer, const_reference>;
     
     MyList() :_size(0) {
         void* place = operator new(sizeof(Node));
         
         last = static_cast<Node*>(place);
            
         first = last;
     }
     MyList(MyList&& other) : first(other.first), last(other.last), _size(other._size)
     {
         other.first = nullptr;
         other.last = nullptr;
         other._size = 0;
     }
     MyList(std::initializer_list<T> init) :MyList() {
         
         for (T x : init) {
             push_back(x);
         }
     }
     
     MyList(iterator start, iterator fin) : MyList() {
         
         while (start != fin)
         {
             push_back(*start++);
         }
     }

     
     MyList(const MyList& other) :MyList(other.begin(), other.end()) {}
     
     MyList& operator=(const MyList& other) {
         clear();
         auto start = other.begin();
         auto fin = other.end();
         while (start != fin)
         {
             push_back(*start++);
         }
         return *this;
     }
     MyList& operator=(MyList&& other) noexcept {
         
         MyList temp{ std::move(other) };
         swap(temp);
         return *this;
     }
     MyList& operator=(std::initializer_list<T> ilist) {
         return operator=(MyList(ilist));
     }
     
     reference front() {
         return first->data;
     }
     const_reference front() const {
         return first->data;
     }
     reference back() {
         if (empty())
             std::exception();
         return (last->prev)->data;
     }
     const_reference back() const {
         if (empty())
             std::exception();
         return (last->prev)->data;
     }
     
     iterator begin() noexcept {
         return iterator(first);
     }
     const_iterator begin() const noexcept {
         return const_iterator(first);
     }
     const_iterator cbegin() const noexcept {
         
         return const_iterator(first);
     }
     iterator end() noexcept {
         return iterator(last);
     }
     const_iterator end() const noexcept {
         return const_iterator(last);
     }
     const_iterator cend() const noexcept {
         return const_iterator(last);
     }

     
     bool empty() const noexcept {
         return _size == 0;
     }
     size_type size() const noexcept {
         return _size;
     }
     
     void clear() noexcept {
         while (!empty())
         {
             pop_front();
         }
         
     }
     
     /// <summary>
     /// вставляет value перед узлом pos
     /// </summary>
     iterator insert(const_iterator pos, const_reference value) {
         Node* ptr = pos.getCurrent();
         if (!ptr)
                throw std::exception("after end of list");
         _size++;
         if (ptr == last)
         {
             push_back(value);
             iterator(ptr->prev);
         }
         Node* n = new Node(value, ptr->prev, ptr);
         if (ptr->prev) {
             ptr->prev->next = n;
         }
         ptr->prev = n;
         return iterator(n);
     }

     /// <summary>
     /// вставляет value перед узлом pos
     /// </summary>
     iterator insert(iterator pos, const_reference value) {
         Node* ptr = pos.getCurrent();
         if (!ptr)
             throw std::exception("after end of list");
         _size++;
         if (ptr == last)
         {
             push_back(value);
             return iterator(ptr->prev);
         }
         Node* n = new Node(value, ptr->prev, ptr);
         if (ptr->prev) {
             ptr->prev->next = n;
         }
         ptr->prev = n;
         return iterator(n);
     }
     iterator insert(const_iterator pos, T&& value) {
         Node* ptr = pos.getCurrent();
         if (!ptr)
             throw std::exception("after end of list");
         _size++;
         if (ptr == last)
         {
             push_back(value);
             iterator(ptr->prev);
         }
         Node* n = new Node(value, ptr->prev, ptr);
         if (ptr->prev) {
             ptr->prev->next = n;
         }
         ptr->prev = n;
         return iterator(n);
     }
     
     iterator erase(iterator pos) {
         Node* ptr = pos.getCurrent();
         if (!ptr || ptr == last)
             throw std::exception("after end of list");
         --_size;
         if (!ptr->prev)
         {
             first = ptr->next;
             first->prev = nullptr;
         }
         else
         {
             ptr->prev->next = ptr->next;
             ptr->next->prev = ptr->prev;
         }
         Node* next = ptr->next;
         delete ptr;
         return iterator(next);
     }
     iterator erase(const_iterator pos) {
         Node* ptr = pos.getCurrent();
         if (!ptr || ptr == last)
             throw std::exception("after end of list");
         --_size;
         if (!ptr->prev)
         {
             first = ptr->next;
         }
         else
         {
             ptr->prev->next = ptr->next;
             ptr->next->prev = ptr->prev;
         }
         Node* next = ptr->next;
         delete ptr;
         return iterator(next);
     }
     iterator erase(iterator _first, iterator _last) {
         iterator cur = _first;
         while (cur != _last)
         {
             
             cur = erase(cur);
         }
         return _last;
     }
     iterator erase(const_iterator _first, const_iterator _last) {
         iterator cur = _first;
         while (cur != _last)
         {
             cur = erase(cur);
         }
         return const_cast<iterator>(_last);
     }
     
     void push_back(const T& value) {
         Node* p = new Node(value, nullptr, last);
         
         _size++;
         if (first == last)
         {
             first = p;
         }
         else {
             Node* tlast = last->prev;
             if (tlast) {
                 tlast->next = p;
                 p->prev = tlast;
                 
             }
         }
         last->prev = p;
         
     }
     void push_back(T&& value) {
         Node* p = new Node(std::move(value), nullptr, last);
         
         _size++;
         if (first == last)
         {
             first = p;
         }
         else {
             Node* tlast = last->prev;
             if (tlast) {
                 tlast->next = p;
                 p->prev = tlast;
                 
             }
         }
         last->prev = p;
     }
        
     void pop_back() {
         
         if (empty())
             throw std::exception("empty list");
         --_size;
         Node* tlast = last->prev;
         
         last->prev = tlast->prev;
         last->prev->next = last;
         delete tlast;
     }
     void push_front(const T& value) {
         _size++;
         Node* p = new Node(value, nullptr, first);
         first->prev = p;
         first = p;
         
         if (last->prev == nullptr)
             last->prev = p;
     }
     void push_front(T&& value) {
         _size++;
         Node* p = new Node(std::move(value), nullptr, first);
         first->prev = p;
         first = p;
         if (last->prev == nullptr)
             last->prev = p;
     }
     void pop_front() {
         if (empty())
             throw std::exception("empty list");
         
         --_size;
         Node* t(first);
         first = first->next;
         first->prev = nullptr;
         delete t;
     }
     
     void swap(MyList& other) noexcept {
         std::swap(first, other.first);
         std::swap(last, other.last);
         std::swap(_size, other._size);
     }
     /*
     void reverse() noexcept {
         MyList<T> copy();
         auto f = new Node(first->data, nullptr, first->next);
         while (f != last)
         {
             copy.push_front(f->data);
             f = f->next();
         }
         operator=(copy);
     }*/
     
     ~MyList() {
         clear();
         operator delete(last);
     }
    
     unsigned int count_of_pos() {
         unsigned int count = 0;

         for (iterator it = begin(); it != end();++it) {
             if (it.getCurrent()->data > 0)
                 ++count;
         }

         return count;
     }

     std::tuple<T, unsigned int> max_elem_count() {
         T mx = front();
         unsigned int count = 1;
         iterator it = ++begin();
         for (; it != end();++it) {
             T cur = it.getCurrent()->data;
             if (cur > mx) {
                 mx = cur;
                 count = 1;
             }
             else
                 if (cur == mx)
                     ++count;
         }
         return { mx,count };
     }

     void split_on_positivity(MyList& pos, MyList& neg) {
         pos.clear();
         neg.clear();
         for (iterator it = begin(); it != end();++it) {
             T cur = it.getCurrent()->data;
             if (cur < 0)
                 neg.push_back(cur);
             else
                 pos.push_back(cur);
         }
     }

     /*void reverse() {
         Node* l = last; 
         std::swap(last->prev, first);
         l = last->prev;
         for (size_t i = 1; i < _size/2;++i) {
             std::swap(l->prev, l->next);
             l = l->prev;
         }
     }*/
};

