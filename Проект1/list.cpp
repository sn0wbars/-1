#pragma once

#define CRT_SECURE_NO_WARNINGS

#include "platypus.h"

const unsigned int MAXnumber = 10000;

//#define TYPEofLIST char
template <typename T>
class node
{
private:
	node* m_prev;
	node* m_next;
	T m_val;
	friend int node_OK(node* N) { return !(N->m_prev) && !(N->m_next)};
	friend bool node_DUMP(const node* <T> N, const char name[], int error = 0);
public:
	node(const T value, node* prev = nullptr, node* next = nullptr) :
		m_val(value), m_prev(prev), m_next(next) {};
	~node() : m_val(-1), m_prev(nullptr), m_next(nullptr) {};
	node* getnext() { return m_next }; // accessor
	node* getprev() { return m_prev }; // accessor
	T getval() { return m_val };
	bool putnext(node* next) { m_next = next };
	bool putprev(node* prev) { m_prev = prev };
	bool putval(T val) { m_val = val };
};

template<typename T>
bool node_DUMP(const node* <T> N, const char name[], int error = 0) //todo: expanse
{
	printf("\nm_prev = %d\n m_next = %d\n m_val = %d\n", N->m_prev, N->m_next, N->m_val);
	return 0;
};

template <typename type> 
class List
{
private:
	node<type> * first, * end;
	int number;
	bool find(node<type>* result, type val);
	friend int List_OK(list* N) { return !(N->first && N->end && (number >= 0)) };
	friend bool List_DUMP(const list* <T> N, const char name[], int error = 0);
public:
	List(type val = 0) : number(1)
	{
		first = new node<type>(n);
		end = first;
	}
	bool push(type val); 
	type pop() 
	{
		ASSERT_OK(this);
		type result = end->getval();
		node<type>* previous = end->getprev;
		delete end;
		end = previous;
		end->putnext(nullptr);
		ASSERT_OK(this);
		return result;
	};
	bool insert();
	bool remove();
	~List();
};

template<typename type>
bool List<type>::push(type val)
{
	ASSERT_OK(this);
	end->putnext(new node<type>(val, end)); // 
	assert(end->getnext());
	end = end->getnext();
	return 1;
}

template<typename type>
type List<type>::pop()
{
	ASSERT_OK(this);
	type result = end->getval();
	node<type>* previous = end->getprev;
	delete end;
	end = previous;
	end->putnext(nullptr);
	ASSERT_OK(this);
	return result;
}

template<typename T>
bool List_DUMP(const list* <T> N, const char name[], int error = 0) //todo: expanse
{ //!!!!!!
	printf("\nm_prev = %d\n m_next = %d\n m_val = %d\n", N->m_prev, N->m_next, N->m_val);
	return 0;
};
template<typename T>
int List_OK(list* N)
{ 
	if (N->first && N->end && (number >= 0) && err) return 0;
	else return 1;
	node* ptr = N->first;
	while (ptr->next)
	{
		ptr = ptr->next;
			if !(node_OK(ptr))
				return 1;
	}
	return 0;
}

//int main()
//{
//	return 0;
//}

//template<typename T>
//inline node<T>::node(const T value, node * prev, node * next)
//{
//
//}

template<typename type>
bool List<type>::find(node<type>* result, type val) // start
{
	ASSERT_OK(this);
	node<type>* ptr = first;
	for (int i = 0; i < lenght; ++i)
	{
		assert (ptr);
		if (ptr->m_val == val)
		{
			result = ptr;
			return 1;
		}
		ptr = ptr->m_next;
	}
	return 0;
}

template<typename type>
inline List<type>::~List()
{
	ASSERT_OK(this);
	node<type>* next = first;
	for (int i = 0; i < number; i++)
	{
		node<type>* step = next;
		next = step->m_next;
		delete step;
		assert(next && (i != number - 1));
	}
} 