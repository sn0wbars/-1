#pragma once

#define ASSERT_OK(type, what)\
{\
int error = type##_OK(what);\
if (error)\
	{\
	printf("OMG! ERROR! ERROR!!11\n" #type " " #what " failed in %s /%s, %d\n",\
	__FILE__, __func__, __LINE__);\
	printf("Error code: %d", error);\
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
	stack_is_broken,
	stack_is_nullptr,
	arr_is_nullptr,
	//	arrPtr_is_nullptr,
	arrPtr_is_less_arr,
	wrong_amount,
};