#pragma once

#define CRT_SECURE_NO_WARNINGS

#include "platypus.h"

const unsigned int MAXnumber = 10000;

//#define TYPEofLIST char
template <typename T>
class node
{
private:
	node<T>* m_prev;
	node<T>* m_next;
	T m_val;
	friend int node_OK(node* N) { return 0; };
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
	void putnext(node* next) { m_next = next; };
	void putprev(node* prev) { m_prev = prev; };
	void putval(T val) { m_val = val; };
	void ok() { node_OK(this); };
	void dump() { node_DUMP(this); };
};

template<typename T>
node<T>::~node()
{
	m_prev = nullptr;
	m_next = nullptr;
	m_val = -1;
}

//template<typename T>
//bool node_DUMP(const node<T>* N, const char name[] = "\"node\"", int error = 0) //todo: expanse
//{
//
//}

template <typename type> 
class List
{
private:
	node<type> * first, * end;
	int number;
	template<typename T>
	friend int List_OK(List<T>*);
	template<typename T>
	friend
	bool List_DUMP(const List<T>* This, const char[], int);
public:
	List(type val = 0) : number(1)
	{
		first = new node<type>(val);
		end = first;
	}
	bool push(type val); 
	type pop();
	bool find(node<type>** result, type val);
	void ok() { List_OK(this); }
	void dump() { List_DUMP(this); }
	bool insert( node<type>* prev, node<type>* next, type val);
	bool remove( node<type>* target);
	~List();
};

template<typename type>
bool List<type>::push(type val)
{
	ASSERT_OK(List, this);

	end->putnext(new node<type>(val, end)); // 
	++number;
	assert(end->getnext());
	end = end->getnext();

	ASSERT_OK(List, this);
	return 1;
}

template<typename type>
type List<type>::pop()
{
	ASSERT_OK(List, this);

	type result = end->getval();
	node<type>* previous = end->getprev();
	delete end;
	end = previous;
	end->putnext(nullptr);
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
	if (!(This->first && This->end && (This->number >= 0))) return 1; // err

	node<T>* ptr = This->first;
	for (int i = 0; i < This->number; ++i)
	{
		if (ptr == nullptr) return 1;
		if (node_OK(ptr)) return 1;
		ptr = ptr->getnext();
	}
	return 0;
};

//template<typename T>
//inline node<T>::node(const T value, node * prev, node * next)
//{
//
//}

template<typename type>
bool List<type>::find(node<type>** result, type val) // start
{
	ASSERT_OK(List, this);

	node<type>* ptr = first;
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

template<typename type>
bool List<type>::insert(node<type>* prev, node<type>* next, type val)
{
	ASSERT_OK(node, prev);
	ASSERT_OK(node, next);
	//if (prev->getnext() != next->getprev()) return 0;

	node<type>* newNode = new node<type>(val, prev, next);
	prev->putnext(newNode);
	next->putprev(newNode);
	++number;

	ASSERT_OK(List, this);
	return 1;
}

template<typename type>
bool List<type>::remove(node<type>* target)
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

template<typename type>
inline List<type>::~List()
{
	ASSERT_OK(List, this);
	node<type>* next = first;
	for (int i = 0; i < number; i++)
	{
		assert(next && (i != number));
		node<type>* step = next;
		next = step->getnext();
		delete step;
	}
} 

int main() // test
{
	
	List <int> a(123);
	
	a.push(12);
	a.push(1111);
	a.push(-123);
	a.pop();
	node <int>* retriver = nullptr;
	a.dump();
	a.find(&retriver, 12);
	a.dump();
	a.insert(retriver, retriver->getnext(), 155);
	a.dump();
}
