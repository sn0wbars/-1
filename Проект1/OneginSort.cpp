// FUPM 571 Borzilov Alexander
// todo: кодовые страницы

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <assert.h>
#include <cerrno>
#include <locale>
#include <stdlib.h>
#include <ctime>
//#include <algorithm>  - for swap

struct mystring
{
	char* str;
	size_t len;
};

size_t Lenght(FILE* file);
int countNumberOfLines(const char buf[],const int len);
int CreateLinesArray(char buf[],const int len,const int numLines, char *line[]);
int strcmpbegin(const void* a, const void* b);
int Write(char *line[], const char fileName[],const int numLines);
int Write(mystring line[], const char fileName[], const int numLines);
FILE* StartDump(const time_t seconds = time(NULL));
bool EndDump(FILE* file, const time_t timeS);
bool SmartPrintText(const char text[], FILE* file, int lenght);
template <typename T> void swap(T* a, T* b);
bool BubbleSort(char** text, int(*compare)(const char str1[], const char str2[]), int N);
bool BubbleSort(char** text, int(*compare)(const void* str1, const void* str2), int N);
int Min(const int a, const int b);
int mystring_strcmpend(const void* a, const void* b);
void mystring_desctor(mystring *This);
void mystring_ctor(mystring *This, const char* str);
inline bool IsLetter(const char s);
void Free(mystring* array, const int Num);

bool dump = 1;
enum method {bubble, quick};

int main()
{
	printf("# -OneginSearch- \n");
	setlocale(LC_ALL, "Russian");

	time_t timeS;
	method SortMode =bubble;
	const char InputName1[11] = "onegin.txt";
	const char OutputName1[24] = "OneginSortFromBegin.txt";
	const char OutputName2[22] = "OneginSortFromEnd.txt";

	FILE* dumpFile = NULL;
	
	if (dump)
	{
		timeS = time(NULL);
		dumpFile = StartDump(timeS);
		if (dumpFile == nullptr)
		{
			dump = 0;
			printf("Can't create dump_file");
		}
	}

	FILE* fInput = fopen(InputName1, "rb");
	if (fInput == nullptr) return perror("Can't open file\nErrno"), __LINE__;

	const int lenght = Lenght(fInput);
	if (lenght < 0) return perror("Negative lenght of file\nErrno"), __LINE__;
	if (dump) fprintf(dumpFile, "Size of file: %d\n", lenght);

	char* buffer = (char*)calloc(lenght, sizeof(*buffer));
	if (buffer == nullptr) return perror("Can't create buffer\nErrno"), __LINE__;

	const int numOfWasRead = (fread_s(buffer, lenght, sizeof(char), lenght, fInput));
	if (dump) fprintf(dumpFile, "Number of read symbols: %d\n", numOfWasRead);
	if(numOfWasRead != lenght) return perror("Number of read symbols isn't equal lenght of file\nErrno"), __LINE__;
	fclose(fInput);
	
	if (dump) 
		if (SmartPrintText(buffer, dumpFile, lenght))
		{
			printf("Dump error, cant print text");
			dump = 0;
		}

	const int numOfLines = countNumberOfLines(buffer, lenght);
	if (numOfLines < 0) return perror("Negative number of lines\nErrno"), __LINE__;

	char** linesArray = (char**)calloc(numOfLines, sizeof(linesArray[0]));
	if (linesArray == nullptr) return perror("Can't create Array of lines\nErrno"), __LINE__;
	if (dump) fprintf(dumpFile, "sizeof(linesArray): %d\nNumber of Lines: %d\n",
		sizeof(linesArray), numOfLines);

	if (CreateLinesArray(buffer, lenght, numOfLines, linesArray))
		return perror("Can't fill array of lines\nErrno"), __LINE__;

	if (SortMode == bubble) BubbleSort(linesArray, *strcmp, numOfLines);
	else qsort(linesArray, numOfLines, sizeof(linesArray[0]), strcmpbegin);
	Write(linesArray, OutputName1, numOfLines);
	if (errno) return perror("Error"), __LINE__;
	
	mystring* stringesArray = (mystring*)calloc(numOfLines,sizeof(stringesArray[0]));
	for (int i = 0; i < numOfLines; ++i)
	{
		mystring_ctor(&stringesArray[i], linesArray[i]);
	}

	qsort(stringesArray, numOfLines, sizeof(stringesArray[0]), mystring_strcmpend);
	Write(stringesArray, OutputName2, numOfLines);
	if (errno) return perror("Error"), __LINE__;

	free(buffer);
	buffer = NULL;
	free(linesArray);
	linesArray = NULL;
	Free(stringesArray, numOfLines);
	free(stringesArray);
	stringesArray == NULL;

	EndDump(dumpFile, timeS);

	return 0;
}

size_t Lenght(FILE* file)
{
	if (file == nullptr) return -1;

	fseek(file, 0, SEEK_END);
	int len = ftell(file);
	rewind(file);

	return len;
}

int countNumberOfLines(const char buf[], const int len)
{
	if (buf == nullptr) return -1;

	int count = 1;
	for (int i = 0; i < len; i++)
		if (buf[i] == '\n') count++;
	return count;
}

int CreateLinesArray(char buf[], const int len, const int numLines, char *line[])
{
	if (buf == nullptr || line == nullptr) return 1;

	int beginOfString = 0, j = 0;
	for (int i = 0; i < numLines-1; ++i, ++j)
	{
		line[i] = buf + j;
		while (j++ < len && buf[j] != '\n') ;
		buf[j] = '\0';
	//	if(dump) printf("%s\n", line[i]);
	}
	line[numLines-1] = buf + j;
	return 0;
}

inline int strcmpbegin(const void* a, const void* b)
{
	return strcmp(*(const char**)a, *(const char**)b);
}

int Write(char *line[], const  char fileName[], const int numLines)
{
	if (line == nullptr) return -1;

	FILE *fOutput = fopen(fileName, "w");
	if (fOutput == nullptr) return 1;
	for (int i = 0; i < numLines; i++)
		fprintf(fOutput, "%s\n", line[i]);
	fclose(fOutput);
	return 0;
}

int Write(mystring line[], const char fileName[], const int numLines)
{
	if (line == nullptr) return -1;

	FILE *fOutput = fopen(fileName, "w");
	if (fOutput == nullptr) return 1;
	for (int i = 0; i < numLines; i++)
		fprintf(fOutput, "%s\n", (&line[i])->str);
	fclose(fOutput);
	return 0;
}

FILE* StartDump(const time_t seconds)
{
	FILE* file = fopen("~OneginSort_dump.txt", "w");
	tm* timeinfo = localtime(&seconds);
	fprintf(file, "%s\n", asctime(timeinfo));
	return file;
}

bool EndDump(FILE* file, const time_t timeS)
{
	long int elTime = time(NULL) - timeS;
	fprintf(file, "%s\nElapsed time: %d seconds\n------------END------------", strerror(errno), elTime);
	fclose(file);
	return 0;
}

bool SmartPrintText(const char text[], FILE* file, int lenght)
{
	if (text == nullptr || file == nullptr)
	{
		errno = EINVAL;
		return 1;
	}

	const char carriage = 39, enter = 35, end = 36;

	fprintf(file, "*****************\n0.0 ");

	int numOfLines = 1;
	for (int i = 0; i < lenght; ++i)
	{
		if (text[i] == '\n')
		{
			bool check = fprintf(file, "%c\n%d.%d ", enter, numOfLines, i);
			assert(check);
			++numOfLines;
		}
		else if (text[i] == '\r') fprintf(file, "%c", carriage);
		else if (text[i] == '\0') fprintf(file, "%c", end);
		else
		{
			bool check = fprintf(file, "%c", text[i]);
			assert(check);
		}
	}

	fprintf(file, "\n*****************\n");
	return 0;
}

bool BubbleSort(char** text, int(*compare)(const char str1[], const char str2[]), int N)
{
	if (text == nullptr || N < 0)
	{
		errno = EINVAL;
		return 1;
	}

	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N - 1; ++j)
			if (compare(text[i], text[j]) < 0)
				std::swap(text[i], text[j]);
	return 0;
}

bool BubbleSort(char** text, int(*compare)(const void* str1, const void* str2), int N)
{
	if (text == nullptr || N < 0)
	{
		errno = EINVAL;
		return 1;
	}

	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N - 1; ++j)
			if (compare(text[i], text[j]) < 0)
				std::swap(text[i], text[j]);
	return 0;
}

template <typename T> inline void swap(T* a, T* b)
{
	T c = *b;
	*b = *a;
	*a = c;
}

inline int mystring_strcmpend(const void* a, const void* b)
{
	const mystring* a2 = (const mystring*)a;
	const mystring* b2 = (const mystring*)b;
//	int min = Min(a2->len, b2->len);

	for (int i = a2->len, j = b2->len; (i >= 0) && (j >= 0);)
	{
		//bool notAlphaA = !isalpha((unsigned char)a2->str[i]);
		////if (dump) printf("%c ~ %c\n", a2->str[i], b2->str[j]);
		//if(notAlphaA)
		//{
		//	--i;
		//	continue;
		//}
		//bool notAlphaB = !isalpha((unsigned char)b2->str[i]);
		//if(notAlphaB)
		//{
		//	--j;
		//	continue;
		//}
		if (a2->str[i] != b2->str[j]) return a2->str[i] - b2->str[j];
		--j;
		--i;
	}
		return 0;
}

inline int Min(const int a, const int b)
{
	return a < b ? a : b;
}

void mystring_ctor(mystring *This, const char* str)
{ 
	This->str = _strdup(str);
	This->len = strlen(str);
}

void mystring_desctor(mystring *This)
{
	free(This->str);
	This->str = NULL;
	This->len = -1;
}

void Free(mystring* array, const int Num)
{
	for (int i = 0; i < Num; ++i)
	{
		mystring_desctor(&array[i]);
	}
}