#include <initializer_list>
#include <memory>
#include <iterator>
#include <exception>


template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;
    Node(T d, Node<T>* p, Node<T>* n) : data(d), prev(p), next(n) {}
};

template<typename T>
class MyList
{
    Node<T>* first;
    Node<T>* last;

public:
    using value_type      = T;
    using size_type       = size_t;
    using difference_type = ptrdiff_t;
    using pointer         = value_type*;
    using const_pointer   = const value_type*;
    using reference       = value_type&;
    using const_reference = const value_type&;

    template<typename Pointer, typename Reference>
    class BaseIterator : public std::iterator<std::bidirectional_iterator_tag, value_type, difference_type, Pointer, Reference>
    {
        
    public:
        Node<T>* p;

        BaseIterator(Node<T>* pp):p(pp){}

        bool operator==(const BaseIterator& other) {
            return p == other.p;
        }
        bool operator!=(const BaseIterator& other) {
            return !(this == other);
        }
        pointer operator->() {
            return this;
        }
        BaseIterator& operator--() {
            if (p->prev == nullptr)
                throw std::exception();
            p = p->prev;
            return *this;
        }
        BaseIterator& operator--(int) {
            if (p->prev == nullptr)
                throw std::exception();
            BaseIterator& t = *this;
            p = p->prev;
            return t;
        }
        BaseIterator& operator++() {
            if (p->next == nullptr)
                throw std::exception();
            p = p->next;
            return *this;
        }
        BaseIterator& operator++(int) {
            if (p->next == nullptr)
                throw std::exception();
            BaseIterator& t = *this;
            p = p->next;
            return t;
        }
        Reference operator*() {
            return *p;
        }
    };

    using iterator               = BaseIterator<pointer, reference>;
    using const_iterator         = BaseIterator<const_pointer, const_reference>;

    MyList() {
        last = new Node<T>(NULL, nullptr, nullptr);
        first = last;
    }
    MyList(const MyList& other) :MyList(other.first, other.last){}
    MyList(MyList&& other) : first(other.first), last(other.last) {
        other.first = nullptr;
        other.last = nullptr;
    }
    MyList(std::initializer_list<T> init) {
        for(auto x:init) {
            push_back(x);
        }
    }

    MyList(iterator start, iterator fin) {
        while (start != fin)
        {
            push_back(*start++);
        }
    }

    MyList& operator=(const MyList& other) {
        if (this != &other)
        {
            while (first != last) {
                Node<T>* t = first;
                ++first;
                delete t;
            }
            iterator start = other.first;
            iterator fin = other.last;
            while (start != fin)
            {
                push_back(*start++);
            }
        }
        return *this;
    }
    MyList& operator=(MyList&& other) noexcept {
        first = other.first;
        last = other.last;
        other.first = nullptr;
        other.last = nullptr;
        return *this;
    }
    MyList& operator=(std::initializer_list<T> ilist) {
        while (first != last) {
            Node<T>* t = first;
            ++first;
            delete t;
        }
        for (auto x : ilist) {
            push_back(x);
        }
        return *this;
    }

    reference front() {
        return &first->data;
    }
    const_reference front() const {
        return &first->data;
    }
    reference back() {
        return &(--last)->data;
    }
    const_reference back() const {
        return &(--last)->data;
    }

    iterator begin() noexcept {
        return BaseIterator<pointer, reference>(first);
    }
    const_iterator begin() const noexcept {
        return BaseIterator<pointer, reference>(first);
    }
    const_iterator cbegin() const noexcept {
        return BaseIterator<pointer, reference>(first);
    }
    iterator end() noexcept {
        return BaseIterator<pointer, reference>(--last);
    }
    const_iterator end() const noexcept {
        return BaseIterator<pointer, reference>(--last);
    }
    const_iterator cend() const noexcept {
        return BaseIterator<pointer, reference>(--last);
    }


    bool empty() const noexcept {
        return first == last;
    }
    size_type size() const noexcept{ 
        return std::distance(first, --last); 
    }

    void clear() noexcept {
        while (first->next )
        {
            Node<T>* t = first;
            first = first->next;
            delete t;
        }
    }


    iterator insert(const_iterator pos, const T& value) {
        if (pos == last)
            throw std::exception("after end of list");
        Node<T>* next = pos.p->next;
        Node<T>* n = new Node<T>(value, pos.p, next);
        next->prev = n;
        pos.p->next = n;
        return BaseIterator<pointer,reference>(n);
    }
    iterator insert(const_iterator pos, T&& value) {
        if (pos == last)
            throw std::exception("after end of list");
        Node<T>* next = pos.p->next;
        Node<T>* n = new Node<T>(value, pos.p, next);
        next->prev = n;
        pos.p->next = n;
        return BaseIterator<pointer, reference>(n);
    }

    iterator erase(iterator pos) {
        if (pos == last)
            throw std::exception("after end of list");
        Node<T>* pr = pos.p->prev;
        Node<T>* next = pos.p->next;
        delete pos;
        pr->next = next;
        next->prev = pr;
        return next;
    }
    iterator erase(const_iterator pos) {
        if (pos == last)
            throw std::exception("after end of list");
        Node<T>* pr = pos.p->prev;
        Node<T>* next = pos.p->next;
        delete pos;
        pr->next = next;
        next->prev = pr;
        return next;
    }
    iterator erase(iterator _first, iterator _last) {
        Node<T>* pr = _first.p->prev;
        Node<T>* next = _last.p->next;
        while (_first != _last) {
            iterator t = _first;
            ++_first;
            delete t;
        }
        pr->next = next;
        next->prev = pr;
        return pr;
    }
    iterator erase(const_iterator _first, const_iterator _last) {
        Node<T>* pr = _first.p->prev;
        Node<T>* next = _last.p->next;
        while (_first != _last) {
            iterator t = _first;
            ++_first;
            delete t;
        }
        pr->next = next;
        next->prev = pr;
        return pr;
    }

    void push_back(const T& value) {
        Node<T>* p = new Node<T>(value, nullptr, last);
        Node<T>* tlast = last->prev;
        last->prev = p;
        if (first == last)
        {
            first = p;
            return;
        }
        tlast->next = p;
        p->prev = tlast;

    }
    void push_back(T&& value) {
        Node<T>* p = new Node<T>(value, nullptr, last);
        Node<T>* tlast = last->prev;
        last->prev = p;
        if (first == last)
        {
            first = p;
            return;
        }
        tlast->next = p;
        p->prev = tlast;
    }
    void pop_back() {
        if(empty())
            throw std::exception("empty list");
        
        Node<T>* tlast = last->prev;
        last->prev = tlast->prev;
        last->prev->next = last;

    }
    void push_front(const T& value) {
        Node<T>* p = new Node<T>(value, nullptr, first);
        if (first != nullptr)
            first->prev = p;
        first = p;
        if (last->prev == nullptr)
            last->prev = p;
    }
    void push_front(T&& value) {
        Node<T>* p = new Node<T>(value, nullptr, first);
        if (first != nullptr)
            first->prev = p;
        first = p;
        if (last->prev == nullptr)
            last->prev = p;
    }
    void pop_front() {
        if (empty())
            throw std::exception("empty list");
        first = first->next;
        first->prev = nullptr;
    }

    void swap(MyList& other) noexcept {
        std::swap(first, other.first);
        std::swap(last, other.last);
    }

    void reverse() noexcept {
        MyList<T> copy = new MyList();
        while (first != last)
        {
            copy.push_front(*first->data);
            ++first;
        }
        this = copy;
    }

    ~MyList() {
        while (first != last) {
            Node<T>* t = first;
            ++first;
            delete t;
        }
    }
};
