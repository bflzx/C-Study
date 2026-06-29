#pragma once

namespace mylist
{
	template<class T>
	struct __list_node
	{
		__list_node<T>* _next;
		__list_node<T>* _prev;
		T _data;
		__list_node(const T& x = T())
			:_data(x)
			,_next(nullptr)
			,_prev(nullptr)
		{
		}
	};

	template<class T>
	struct __list_iterator
	{
		typedef __list_node<T> Node;
		Node* _node;
		__list_iterator(Node* node)
			:_node(node)
		{
		}
		T& operator*()
		{
			return _node->_data;
		}
		__list_iterator<T>& operator++()
		{
			_node = _node->_next;
			return *this;
		}
		__list_iterator<T> operator++(int)
		{
			__list_iterator<T> tmp(*this);
			_node = _node->_nxet;
			return tmp;
		}
		__list_iterator<T>& operator--()
		{
			_node = _node->_prev;
			return *this;
		}
		bool operator!=(__list_iterator<T>& it)
		{
			return _node != it->_node;
		}
		bool operator==(__list_iterator<T>& it)
		{
			return _node == it->_node;
		}
		T* operator->()
		{
			return &_node->_data;
		}
	};

	template<class T>
	class list
	{
		typedef __list_node<T> Node;
	public:
		//带头双向循环链表
		typedef __list_iterator<T,T&,T*> iterator;
		typedef __list_iterator<T, const T&, const T*> const_iterator;

		iterator begin()
		{
			return iterator(_head->_next);
		}
		iterator end()
		{
			return iterator(_head);
		}
		list()
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
		}
		list(const list<T>& lt)
		{

		}
		lsit<T>& operator=(const list<T>& lt)
		{

		}
		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}
		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				erase(it++);
			}
		}
		void push_back(const T& x)
		{
			Node* tail = _head->_prev;
			Node* newnode = new Node(x);
			tail->_next = newnode;
			newnode->_prev = tail;
			newnode->_next = _head;
			_head->_prev = newnode;
		}
		void pop_back()
		{
		}
		void push_front(const T& x)
		{
		}
		void insert(iterator pos, const T& x)
		{

		}
		void erase(iterator pos)
		{

		}
	private:
		Node* _head;
	};
}