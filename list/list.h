#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "platypus.h"

const unsigned int MAXnumber = 10000;

template <typename T>
class node
{
private:
	node<T>* m_prev;
	node<T>* m_next;
	T m_val;
	friend int node_OK(node* N) { if (N == nullptr) return 1; else return 0; };
	friend bool node_DUMP(const node<T>* N, const char name[] = "\"node\"", int error = 0)
	{
		assert(N);
		if (error) printf("ERROR in node %s\n", name);
		printf(" m_prev = %p\n m_next = %p\n m_val = %d\n", N->m_prev, N->m_next, N->m_val);
		return 0;
	};
public:
	node(const T value, node* prev = nullptr, node* next = nullptr) :
		m_val(value), m_prev(prev), m_next(next) {};
	~node();
	node<T>* getnext() { return m_next; }; // accessor
	node<T>* getprev() { return m_prev; }; // accessor
	T getval() { return m_val; };
	void putnext(node* next) { this->ok(); next->ok(); m_next = next; };
	void putprev(node* prev) { this->ok(); prev->ok(); m_prev = prev; };
	void putval(T val) { m_val = val; };
	void ok() { node_OK(this); };
	void dump() { node_DUMP(this); };
};

template<typename T>
node<T>::~node()
{
	m_prev = nullptr;
	m_next = nullptr;
//	m_val = -1;
}

template <typename T> 
class List
{
private:
	node<T> * first, * end;
	int number;
	template<typename T>
	friend int List_OK(List<T>*);
	template<typename T>
	friend
	bool List_DUMP(const List<T>* This, const char[], int);
public:
	List(T val = 0) : number(1)
	{
		first = new node<T>(val);
		end = first;
	}
	bool push(T val); 
	T pop();
	bool find(node<T>** result, T val);
	void ok() { List_OK(this); }
	void dump() { List_DUMP(this); }
	bool insert( node<T>* prev, node<T>* next, T val);
	bool remove( node<T>* target);
	bool isfstnull() { return !(first->getval()); };
	~List();
	size_t getLen() 
	{
		size_t len = 0;
		node<T>* curNode = first;
		for (len; curNode; ++len)
			curNode = curNode->getnext();
		return len;
	};
};

template<typename T>
bool List<T>::push(T val)
{
	ASSERT_OK(List, this);
	if (end == nullptr)
	{
		node<T>* new_node = new node<T>(val);
		first = new_node;
		end = new_node;
	}
	else
	{
		end->putnext(new node<T>(val, end)); // 
		assert(end->getnext());
		end = end->getnext();
	}
	++number;
	ASSERT_OK(List, this);
	return 1;
}

template<typename T>
T List<T>::pop()
{
	ASSERT_OK(List, this);

	T result = end->getval();
	node<T>* previous = end->getprev();
	delete end;
	if (previous == nullptr)
	{
		first = nullptr;
		end = nullptr;
	}
	else
	{
		end = previous;
		end->putnext(nullptr);
	}
	--number;

	ASSERT_OK(List, this);
	return result;
};

template<typename T>
bool List_DUMP(const List<T>* This, const char name[] = "List", int error = 0)
{
	assert(This);

	FILE* dumpFile = fopen("List_dump.txt", "a");\
		if (dumpFile == nullptr) return printf("Can't create a dump file"), 0;
	fprintf(dumpFile, __TIME__ " " __DATE__"\n");
	if (error) fprintf(dumpFile, "OMG! ERROR! ERROR!!11\n\n\"List\" %s failed in %s/%s, %d\n",
		name, __FILE__, __func__, __LINE__);
	fprintf(dumpFile, "********************************************\n");
	fprintf(dumpFile, " first = %d\n end = %d\n number = %d\n\n", 
		This->first, This->end, This->number);
	if (!error || error == some_sort_of_error)
	{
		unsigned int i = 0;
		node<T>* elem = This->first;
		if (elem)
		{
			fprintf(dumpFile, "%d. %p\n", i++, This->first);
			fprintf(dumpFile, "  m_prev = %p\n  m_next = %p\n  m_val = %d\n\n",
				elem->getprev(), elem->getnext(),elem->getval());
		}
		while (elem->getnext())
		{
			elem = elem->getnext();
			fprintf(dumpFile, "%d. %p\n", i++, elem);
			fprintf(dumpFile, "  m_prev = %p\n  m_next = %p\n  m_val = %d\n\n",
				elem->getprev(), elem->getnext(), elem->getval());
		}

	}
	fprintf(dumpFile, "********************************************\n\n\n");
	fclose(dumpFile);
	return 1;
};


template<typename T>
int List_OK(List<T>* This)
{ 

	if (This->number == 0) return 0;
	if (!(This->first && This->end && (This->number >= 0))) return 1; // err
	node<T>* ptr = This->first;

	for (int i = 0; i < This->number; ++i)
	{
		if (node_OK(ptr)) return 1;
		ptr = ptr->getnext();
	}

	return 0;
};

template<typename T>
bool List<T>::find(node<T>** result, T val) // start
{
	ASSERT_OK(List, this);

	node<T>* ptr = first;
	for (int i = 0; i < number; ++i)
	{
		assert(ptr);
		if (ptr->getval() == val)
		{
			*result = ptr;
			return 1;
		}
		ptr = ptr->getnext();
	}
	ASSERT_OK(List, this);
	return 0;
}

template<typename T>
bool List<T>::insert(node<T>* prev, node<T>* next, T val)
{
	ASSERT_OK(node, prev);
	ASSERT_OK(node, next);
	//if (prev->getnext() != next->getprev()) return 0;

	node<T>* newNode = new node<T>(val, prev, next);
	prev->putnext(newNode);
	next->putprev(newNode);
	++number;

	ASSERT_OK(List, this);
	return 1;
}

template<typename T>
bool List<T>::remove(node<T>* target)
{
	ASSERT_OK(node, target);

	if (target->getprev != nullptr)
		(target->getprev)->putnext(target->getnext);
	if (target->getnext != nullptr)
		(target->getnext)->putprev(target->getprev);
	--number;

	ASSERT_OK(List, this);
	return 0;
}

template<typename T>
inline List<T>::~List()
{
	ASSERT_OK(List, this);
	node<T>* next = first;
	for (int i = 0; i < number; i++)
	{
		assert(next && (i != number));
		node<T>* step = next;
		next = step->getnext();
		delete step;
	} //todo: poison
} 

