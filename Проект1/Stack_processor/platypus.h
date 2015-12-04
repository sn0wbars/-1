#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

#define υμ 

#ifdef TYPEofCPU
#define TYPEofNUMBERS TYPEofCPU
#else
#define TYPEofNUMBERS int // char or int or double
#endif

const bool DUMP_ON = true;
const int MAX_LENGTHofCOMMAND = 8;
const int SIZEofTYPEofNUMBERS = sizeof(TYPEofNUMBERS);
const int MAX_PROGRAM_SIZE = 250;
const char SIGNATURE[] = "BRZ";

#define ASSERT_OK(type, what)\
{\
int error = type##_OK(what);\
if (error)\
	{\
	printf("OMG! ERROR! ERROR!!11\n" #type " " #what " failed in %s /%s, %d\n",\
	__FILE__, __func__, __LINE__);\
	printf("Error code: %d\n", error);\
	if (error != stack_is_nullptr) type ## _DUMP(what, #what, error);\
	abort();\
	}\
}

#define ACTIVATE_SELF_DESTRUCTION(Type, What)\
{\
	printf(#Type #What" : I failed you...");\
	Type ## _dctor(What);\
}

enum stack_errors
{
	no_error,
	some_sort_of_error,
	stack_is_broken,
	stack_is_nullptr,
	arr_is_nullptr,
	//	arrPtr_is_nullptr,
	arrPtr_is_less_arr,
	wrong_amount,
};

size_t Lenght(FILE* file)
{
	if (file == nullptr) return -1;

	fseek(file, 0, SEEK_END);
	int len = ftell(file);
	rewind(file);

	return len;
}