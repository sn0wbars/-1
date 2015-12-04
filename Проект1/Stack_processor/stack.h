#ifndef STACK_H_INCLUDED 
#define STACK_H_INCLUDED

#include "platypus.h"
 
#define TYPEofSTACK int 

const unsigned int MAXmemory = 33554432;

struct Stack
{
	void* arr; // 
	void* arrPtr;
	size_t amount; // number of elements
	size_t size; // number of allocated bytes for stack 
	bool state = false;
};

inline TYPEofSTACK* ACCESS(void* a)
{
	return (TYPEofSTACK*)a;
}

int Stack_OK(Stack* This)
{
	if (This == nullptr) return This->state = 0, stack_is_nullptr;
	if (!This->state) return stack_is_broken;
	TYPEofSTACK* arr = ACCESS(This->arr);
	TYPEofSTACK* arrPtr = ACCESS(This->arrPtr);
	if (arr == nullptr) return This->state = 0, arr_is_nullptr;
	//if (arrPtr == nullptr) return This->state = 0, arrPtr_is_nullptr;
	if (!(arrPtr == nullptr))
	{
		if (arrPtr - arr < 0) return This->state = 0, arrPtr_is_less_arr;
		if (This->amount < (int)(arrPtr - arr)) return This->state = 0, wrong_amount;
	}
	return This->state = 1, no_error; υμ
}
bool Stack_DUMP(const Stack* This, const char name[], int error = 0)
{
	assert(This);

	FILE* dumpFile = fopen("Stack_dump.txt", "a"); \
		if (dumpFile == nullptr) return printf("Can't create a dump file"), 0;
	fprintf(dumpFile, __TIME__ " " __DATE__"\n");
	if (error) fprintf(dumpFile, "OMG! ERROR! ERROR!!11\n\nStack %s failed in %s/%s, %d\n",
		name, __FILE__, __func__, __LINE__);
	fprintf(dumpFile, "********************************************\n");
	fprintf(dumpFile, " arr = %d\n arrPtr = %d\n size = %d\n amount = %d\n state = %d\n",
		ACCESS(This->arr), ACCESS(This->arrPtr), This->size, This->amount, This->state);
	if (!error || error == wrong_amount || error == some_sort_of_error)
		for (int i = 0; i*sizeof(TYPEofSTACK) < This->size; ++i)
		{
			fprintf(dumpFile, "arr[%d]: %d", i, ACCESS(This->arr)[i]);
			if (i < (int)This->amount) fprintf(dumpFile, " *\n");
			else fprintf(dumpFile, "\n");
		}
	fprintf(dumpFile, "********************************************\n\n\n");
	fclose(dumpFile);
	return 1;
}

bool Stack_ctor(Stack* This, size_t buffer = 32)
{
	assert(This);
	bool st = 1;

	This->amount = 0;
	if (buffer > MAXmemory)
	{
		st = 0;
		buffer = MAXmemory;
	}
	This->size = buffer;
	This->arr = calloc(buffer, sizeof(TYPEofSTACK));
	This->arrPtr = nullptr;
	This->state = true;

	ASSERT_OK(Stack, This);
	return st;
}
bool Stack_dctor(Stack* This)
{
	ASSERT_OK(Stack, This)
		free(This->arr);
	This->arr = NULL;
	This->arrPtr = NULL;
	This->amount = -1;
	This->size = -1;
	This->state = 0;

	return 1;
}


bool Stack_realloc(Stack* This)
{
	ASSERT_OK(Stack, This);
	This->size *= 2;
	This->arr = realloc(ACCESS(This->arr), This->size);
	This->arrPtr = ACCESS(This->arr) + This->amount;
	ASSERT_OK(Stack, This);
}

bool Stack_push(Stack* This, TYPEofSTACK val)
{
	ASSERT_OK(Stack, This);

	if ((This->amount + 1) * sizeof(TYPEofSTACK) > This->size)
	{
		if (This->size < MAXmemory)
			if (!Stack_realloc(This))
				return 0;
		else return 0;
	}

	else if (This->arrPtr == nullptr) This->arrPtr = This->arr;
	else This->arrPtr = ACCESS(This->arrPtr) + 1;

	*ACCESS(This->arrPtr) = val;
	++This->amount;

	ASSERT_OK(Stack, This);
	return 1;

}
bool Stack_pop(Stack* This, TYPEofSTACK* val)
{
	ASSERT_OK(Stack, This);
	assert(val);

	if (This->arrPtr == nullptr)
		return 0;

	*val = *ACCESS(This->arrPtr);
	--This->amount;
	if (This->arrPtr == This->arr)
		This->arrPtr = nullptr;
	else This->arrPtr = ACCESS(This->arrPtr) - 1;

	ASSERT_OK(Stack, This);
	return 1;
}

//
//int main() // stack test
//{
// Stack dima;
// assert(Stack_ctor(&dima, 5));
// assert(Stack_push(&dima, 102));
// Stack_push(&dima, 102);
// Stack_push(&dima, 102);
// char a;
// assert(Stack_pop(&dima, &a));
// (Stack_pop(&dima, &a));
// (Stack_pop(&dima, &a));
// (Stack_pop(&dima, &a));
// (Stack_pop(&dima, &a));
// Stack_DUMP(&dima, "dima");
// printf("%d", a);
// Stack_dctor(&dima);
// return 0;
//}

#endif
