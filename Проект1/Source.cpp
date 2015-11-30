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



//bool disasm_jump(FILE* fInput, FILE* fOutput)
//{
//	static int number_of_marks = 0;
//
//	const char mark[MAX_LENGTHofCOMMAND] = { "MARK" };
//	int numMark = 0;
//	int numCommand = -1;
//	char command = 0;
//	char string[MAX_LENGTHofCOMMAND] = {};
//
//	fscanf(fInput, "%d", &numMark);
//	long int positionInput = ftell(fInput);
//	long int positionOutput = ftell(fOutput);
//
//	fseek(fOutput, 0, SEEK_SET);
//	while (fscanf(fOutput, "%d", string) != EOF)
//	{
//		++numCommand;
//		if (string[0] == ':')
//			numCommand -= 2;
//		if (_stricmp(string, "PUSH") == 0) numCommand += SIZEofTYPEofNUMBERS - 1;
//		if (numCommand == numMark)
//		{
//			fprintf(fOutput, ": \n%s%d", mark, number_of_marks);
//			fseek(fOutput, positionOutput, SEEK_SET);
//			return 1;
//		}
//		if (errno) return print_error(fOutput, "jump"), 0;
//	}
//	while (fscanf(fOutput, "%d", string) != EOF)
//
//
//		++number_of_marks;
//	return 0;
//}