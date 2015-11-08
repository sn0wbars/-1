#pragma once

#include "stack.h"
#include <assert.h>
//#include "codes.h"
//#include <math.h>
//#include <errno.h>

#define TYPEofCPU char


struct Cpu
{
	TYPEofCPU ax;
	Stack stack;
};

bool Cpu_ctor(Cpu* This, size_t buffer = 32)
{
	assert(This);
	if (Stack_ctor(&This->stack, buffer))
	{
		ASSERT_OK(Cpu, This);
		return 1;
	}
	else
	{
		ASSERT_OK(Cpu, This);
		return 0;
	}
}

bool Cpu_dctor(Cpu* This)
{
	ASSERT_OK(Cpu, This);
	This->ax = -1;
	Stack_dctor(&This->stack);

	return 1;
}

int Cpu_OK(Cpu* This) // пока почти бессмысленен
{
	assert(This);
	return Stack_OK(&This->stack);
}
bool Cpu_DUMP(const Cpu* This, const char name[], int error = 0)
{
	assert(This);
	printf("ax = %d\n", This->ax);
	Stack_DUMP(&This->stack, name, error);
	printf("You can find more information in Stack_dump.txt :P");
	return 1;
}
bool Cpu_push(Cpu* This, TYPEofCPU value)
{
	ASSERT_OK(Cpu, This);
	if (Stack_push(&This->stack, value))
	{
		ASSERT_OK(Cpu, This);
		return 1;
	}
	ACTIVATE_SELF_DESTRUCTION(Cpu, This);
	return 0;
}
bool Cpu_push_ax(Cpu* This,)
{
	ASSERT_OK(Cpu, This);

}
bool Cpu_pop_ax(Cpu* This,)
{
	ASSERT_OK(Cpu, This);

}