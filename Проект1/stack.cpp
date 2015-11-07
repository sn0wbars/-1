#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

#define TYPE char


#define ASSERT_OK(type, what)\
{\
int error = type##_OK(what);\
if (error)\
	{\
	printf("OMG! ERROR! ERROR!!11\n"#type' '#what" failed in %s/%s, %d\n", __FILE__, __func__, __LINE__);\
	printf("Error code: %d", error);\
	if (error != 0) type##_DUMP(what, #what);\
	abort();\
	}\
}\
//type##_DUMP(what);\
//if (dump || error) type##_DUMP(what, #what, error);\
  
enum stack_errors
{
	broken,
	stack_is_nullptr,
	arr_is_nullptr,
	arrPtr_is_nullptr,
	arrPtr_is_less_arr,
	wrong_amount,
};

struct Stack
{
	void* arr;
	void* arrPtr;
	size_t amount;
	size_t size;
	bool state = false;
};

bool Stack_ctor(Stack* This, size_t buffer)
{
	assert (This);
	This->arrPtr = NULL;
	This->amount = 0;
	This->size = buffer;
	This->arr = calloc(buffer, sizeof(TYPE));
	This->state = true;
	
	return 1;
}

bool Stack_dctor(Stack* This)
{
	ASSERT_OK(Stack, This);
	free(This->arr);
	This->arr = NULL;
	This->arrPtr = NULL;
	This->amount = -1;
	This->size = -1;
	This->state = 0;
}

bool Stack_push(Stack* This, TYPE value) //!
{
	ASSERT_OK(Stack, This);
	if (This->amount == (This->size) * sizeof(TYPE))
		realloc(ACCESS(This->arr), sizeof(TYPE) * 2 * This->size);
		  
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
	if (This->amount < arrPtr - arr) return This->state = 0, wrong_amount;
}

bool Stack_DUMP(const Stack* This, const char name[], int error = 0)
{
	FILE* dumpFile = fopen("Stack_dump.txt", "a");\
	if (dumpFile == nullptr) return printf("Can't create a dump file"), 0;
	fprintf(dumpFile, __DATE__"\n\n");
	if (error) fprintf(dumpFile, "OMG! ERROR! ERROR!!11\n\nStack %s failed in %s/%s, %d\n",name, __FILE__, __func__, __LINE__);
	fprintf(dumpFile,"********************");
	fprintf(dumpFile, " arr = %d/n arrPtr = %d/n size = %d/n amount = %d/n state = %d/n",
		ACCESS(This->arr), ACCESS(This->arrPtr), This->size, This->amount, This->state);
	if (error == 0 || error == wrong_amount)
		for (int i = 0; i < This->amount; ++i)
			fprintf(dumpFile,"%d. %d", i, ACCESS(This->arr)[i]);
	fprintf(dumpFile, "********************");
	fclose(dumpFile);
	return 0;
}

inline TYPE* ACCESS(void* a)
{
	return (TYPE*)a;
}
int main()
{

	return 0;
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
