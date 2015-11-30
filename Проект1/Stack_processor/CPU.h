#pragma once

#include "stack.h"
#include <math.h>
#include "platypus.h"

#ifdef TYPEofNUMBERS
#define  TYPEofCPU TYPEofNUMBERS
#else
#define TYPEofCPU int // char or int or double
#endif


#define Cpu_op(This, op)\
{\
	ASSERT_OK(Cpu, This);\
	TYPEofCPU a = 0, b = 0, result = 0;\
	if (Stack_pop(&This->stack, &a) && Stack_pop(&This->stack, &b))\
	{\
		ASSERT_OK(Cpu, This);\
		result = a op b;\
		Cpu_push(This, result);\
	}\
	else\
	{\
		This->state = 0;\
		ASSERT_OK(Cpu, This);\
	}\
}

#define Cpu_j(This, op)\
{\
	ASSERT_OK(Cpu, This);\
	TYPEofCPU a = 0, b = 0;\
	if (Stack_pop(&This->stack, &a) && Stack_pop(&This->stack, &b))\
	{\
		ASSERT_OK(Cpu, This);\
		if (a op b) i = cmd[i+1];\
		else i+=2;\
		Cpu_push(This, b);\
		Cpu_push(This, a);\
	}\
	else\
	{\
		This->state = 0; \
		ASSERT_OK(Cpu, This);\
	}\
}


struct Cpu
{
	TYPEofCPU ax;
	TYPEofCPU bx;
	TYPEofCPU cx;

	Stack stack;

	bool state = 0;
};


int Cpu_OK(Cpu* This) // пока почти бессмысленен
{
	assert(This);
	if (!This->state) return 1;
	else return (Stack_OK(&This->stack));
}

bool Cpu_DUMP(const Cpu* This, const char name[]="Cpu.stack", int error = 0)
{
	assert(This);
	printf("ax = %d\n", This->ax);
	Stack_DUMP(&This->stack, name, error);
	printf("You can find more information in Stack_dump.txt :P\n");
	return 1;
}

bool Cpu_ctor(Cpu* This, size_t buffer = 32)
{
	assert(This);
	if (Stack_ctor(&This->stack, buffer))
	{
		This->ax = 0;
		This->state = 1;
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
	This->state = 0;
	This->ax = -1;
	Stack_dctor(&This->stack);

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
	This->state = 0;
	ASSERT_OK(Cpu, This);
	return 0;
	//ACTIVATE_SELF_DESTRUCTION(Cpu, This);
}

bool Cpu_push_ax(Cpu* This)
{
	ASSERT_OK(Cpu, This);
	return Cpu_push(This, This->ax);
}

bool Cpu_pop_ax(Cpu* This)
{
	ASSERT_OK(Cpu, This);
	if (Stack_pop(&This->stack, &This->ax))
	{
		ASSERT_OK(Cpu, This);
		return 1;
	}
	This->state = 0;
	ASSERT_OK(Cpu, This);
	return 0;
}


bool Cpu_pop(Cpu* This)
{
	ASSERT_OK(Cpu, This);
	int val;
	if (Stack_pop(&This->stack, &This->ax))
	{
		ASSERT_OK(Cpu, This);
		return 1;
	}
	This->state = 0;
	ASSERT_OK(Cpu, This);
	return 0;
}

bool Cpu_push_bx(Cpu* This)
{
	ASSERT_OK(Cpu, This);
	return Cpu_push(This, This->bx);
}

bool Cpu_pop_bx(Cpu* This)
{
	ASSERT_OK(Cpu, This);
	if (Stack_pop(&This->stack, &This->bx))
	{
		ASSERT_OK(Cpu, This);
		return 1;
	}
	This->state = 0;
	ASSERT_OK(Cpu, This);
	return 0;
}

bool Cpu_push_cx(Cpu* This)
{
	ASSERT_OK(Cpu, This);
	return Cpu_push(This, This->cx);
}

bool Cpu_pop_cx(Cpu* This)
{
	ASSERT_OK(Cpu, This);
	if (Stack_pop(&This->stack, &This->cx))
	{
		ASSERT_OK(Cpu, This);
		return 1;
	}
	This->state = 0;
	ASSERT_OK(Cpu, This);
	return 0;
}

bool Cpu_pow(Cpu* This)
{
	ASSERT_OK(Cpu, This);
	TYPEofCPU a = 0, b = 0;
	if (Stack_pop(&This->stack, &a) && Stack_pop(&This->stack, &b))
	{
		ASSERT_OK(Cpu, This);
		return Cpu_push(This, (TYPEofCPU) pow((double)b,(double)a));
	}
	This->state = 0;
	ASSERT_OK(Cpu, This);
	return 0;
}

bool Cpu_out(Cpu* This)
{
	ASSERT_OK(Cpu, This);
	TYPEofCPU top = 0;
	if (Stack_pop(&This->stack, &top))
	{
		ASSERT_OK(Cpu, This);
		printf("%d\n", top);
		return 1;
	}
	This->state = 0;
	ASSERT_OK(Cpu, This);
	return 0;
}

bool Cpu_dup(Cpu* This)
{
	ASSERT_OK(Cpu, This);
	TYPEofCPU top = 0;
	if (Stack_pop(&This->stack, &top))
	{
		ASSERT_OK(Cpu, This);
		Cpu_push(This, top);
		Cpu_push(This, top);
		return 1;
	}
	This->state = 0;
	ASSERT_OK(Cpu, This);
	return 0;
}

bool Cpu_sqrt(Cpu* This)
{
	ASSERT_OK(Cpu, This);
	TYPEofCPU a = 0;
	if (Stack_pop(&This->stack, &a))
	{
		ASSERT_OK(Cpu, This);
		return Cpu_push(This, (TYPEofCPU)sqrt((double)a));
	}
	This->state = 0;
	ASSERT_OK(Cpu, This);
	return 0;
}

bool Cpu_in(Cpu* This)
{
	ASSERT_OK(Cpu, This);

	TYPEofCPU val;
	if (scanf("%d", &val))
	{
		Cpu_push(This, val);
		return 1;
	}
	else
	{
		This->state = 0;
		ASSERT_OK(Cpu, This);
		return 0;
	}
}

bool Cpu_exe(Cpu* This, const char cmd[])
{
	unsigned int i = 0;
	while (cmd[i])
	{
		switch (cmd[i])
		{
			#define DEF_CMD(name, num, code, codeAsm, codeDisasm)\
			case num:\
			{\
				code\
				if (DUMP_ON) Cpu_DUMP(This);\
			}\
			break;
			#include "CmdList.h"
			default: printf("No such command: %d", cmd[i]);//!
			#undef DEF_CMD
		}
	}
	return 1;
}

//int main() //test
//{
//	Cpu processor;
//	assert(Cpu_ctor(&processor));
//
//	char massive[] = { 1, 6, 39, 0, 0, 1, 101, 0, 0, 0, 9, 1, 0, 0, 0, 1, 10, 4, 9, 0};
//	Cpu_exe(&processor, massive);
//	Stack_DUMP(&processor.stack,"stk");
//	Cpu_dctor(&processor);
//	return 0;
//}

//Cpu_DUMP(This);\