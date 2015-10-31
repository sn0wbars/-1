#include <stdio.h>
#include <errno.h>
#include <assert.h>

#define TYPE char

#define ASSERT_OK(type, what)\
{\
int error = type##_OK(what);\
if (error)\
	{\
	printf("OMG! ERROR! ERROR!!11\n"#type' '#what" failed in %s/%s, %d", __FILE__, __func__, __LINE__);\
	type##_DUMP(what);\
	abort();\
	}\
}\

//if (dump || error) type##_DUMP(what, #what, error);\

enum stack_errors
{
	broken,
	stack_is_nullptr,
	arr_is_nullptr,
	arrPtr_is_nullptr,
	arrPtr_is_less_arr,
	wrong_size,
};

struct Stack
{
	void* arr;
	void* arrPtr;
	size_t size;
	bool state;
};

bool Stack_push(Stack* This, int value) //!
{
	ASSERT_OK(Stack, This);

}

int Stack_OK(Stack* This)
{
	if (This == nullptr) return This->state = 0, stack_is_nullptr;
	if (!This->state) return broken;
	TYPE* arr = ACCESS(This->arr);
	TYPE* arrPtr = ACCESS(This->arrPtr);
	if (arr == nullptr) return This->state = 0, arr_is_nullptr;
	if (arrPtr == nullptr) return This->state = 0, arrPtr_is_nullptr;
	if (arrPtr - arr < 0) return This->state = 0, arrPtr_is_less_arr;
	if (This->size < arrPtr - arr) return This->state = 0, wrong_size;
}

bool Stack_DUMP(const Stack* This, const char name[], int error = 0)
{
	if (This == nullptr) printf("Can't create a dump file");
	FILE* dumpFile = fopen("Stack_dump.txt", "a");
	fprintf(dumpFile, __DATE__"\n\n");
	if (error) fprintf(dumpFile, "OMG! ERROR! ERROR!!11\n\nStack %s failed in %s/%s, %d\n",name, __FILE__, __func__, __LINE__);
	fprintf(dumpFile,"********************");
	if (error == 0 || error == wrong_size)
		for (int i = 0; i < This->size; ++i)
			fprintf(dumpFile,"%d. %d", i, ACCESS(This->arr)[i]);
	fprintf(dumpFile, "********************");
	fclose(dumpFile);
}

void Stack_ctor(Stack* This);
{
	assert(Stack.OK(This));

}

inline TYPE* ACCESS(void* a)
{
	return (TYPE*)a;
}
int main()
{

}

////////
//enum Commands
//{
//cmdPUSH = 1,
//cmdPOP = 2,
//cmdADD = 3,
//
//};
// Файл CmdList.h
DEF_CMD(PUSH, 1, { stackPush(&stk,v) })
DEF_CMD(POP, 2, { stackPop(&stk,v) })
DEF_CMD(ADD, 3)
if (stricmp(str, "PUSH") == 0)
fprintf(out, "%d", CmdPUSH);
else if 

//asm.cpp #define DEF_CMD(name,num) cmd_##name = num // ,
enum Commands
{
#include "CmdList.h"
	cmd_Last
};

#undef DEF_CMD

#define DEF_CMD(name, num)\
if(stricmp(str, #name) == 0)\
fprintf(out, "%d", num) // num == Cmd_##name деревья хешмапы. В свитчах двоичныйс поиск
else
#include "CmsList.h"

printf("Error ... ");


#define DEFCMD(name, num)\
	{cmd_##name, #name},
const CmdInfo Info[]=
{
#include "CmdList.h"
};
#undef DEFCMD;

// processor
switch (cmd[i])
{
#define DEFCMD(name, num, code)
case num: 
{
	code
}
break;
#include "CmdList.h"
#undef DEFCMD
default: //error
}

//Скриптовый язык
// SqEq.bin : 
//run: SqEq.bin
//	proc SqEq.bin
//	make run

//run.bat
// asm\asm SqEq.asm %1.asm
// proc\cpu SqEq.bin %1.bin
// far
// 

//ТЫ.bat
// @echo Сам %1
// ты дурак
