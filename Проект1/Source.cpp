#define _CRT_SECURE_NO_WARNINGS

#define op(i) {5 i 6}
#include <iostream>
int main()
{
	int c op(+);
	FILE* test;
	fopen_s(&test, "test.txt", "wb");
	fprintf(test, "test");
	char tre[10] = {};
	fscanf(test, tre);
	printf("%s", tre);
	return 0;
}

//bool Cpu_add(Cpu* This)
//{
//	ASSERT_OK(Cpu, This);
//	TYPEofCPU a = 0, b = 0;
//	if (Stack_pop(&This->stack, &a) && Stack_pop(&This->stack, &b))
//	{
//		ASSERT_OK(Cpu, This);
//		return Cpu_push(This, a + b);
//	}
//	ASSERT_OK(Cpu, This);
//	return 0;
//}
//
//bool Cpu_sub(Cpu* This)
//{
//	ASSERT_OK(Cpu, This);
//	TYPEofCPU a = 0, b = 0;
//	if (Stack_pop(&This->stack, &a) && Stack_pop(&This->stack, &b))
//	{
//		ASSERT_OK(Cpu, This);
//		return Cpu_push(This, a - b);
//	}
//	ASSERT_OK(Cpu, This);
//	return 0;
//}
//
//bool Cpu_mul(Cpu* This)
//{
//	ASSERT_OK(Cpu, This);
//	TYPEofCPU a = 0, b = 0;
//	if (Stack_pop(&This->stack, &a) && Stack_pop(&This->stack, &b))
//	{
//		ASSERT_OK(Cpu, This);
//		return Cpu_push(This, a * b);
//	}
//	ASSERT_OK(Cpu, This);
//	return 0;
//}
//
//bool Cpu_div(Cpu* This)
//{
//	ASSERT_OK(Cpu, This);
//	TYPEofCPU a = 0, b = 0;
//	if (Stack_pop(&This->stack, &a) && Stack_pop(&This->stack, &b))
//	{
//		ASSERT_OK(Cpu, This);
//		return Cpu_push(This, a / b);
//	}
//	ASSERT_OK(Cpu, This);
//	return 0;
//}