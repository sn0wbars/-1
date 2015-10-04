// FUPM 571 Borzilov Alexander

#include <stdio.h>
#include <assert.h>
#include <cerrno>
#include <locale>
#include <stdlib.h>
#include <ctime>

struct mystring
{
	char* str;
	size_t len;
};

size_t Lenght(FILE* file);
int countNumberOfLines(char buf[], int len);
int CreateStringArray(char buf[], int len, int numLines, char *line[]);
int strcmpbegin(const void* a, const void* b);
int Write(char *line[], char fileName[], int numLines);
int Write(mystring line[], char fileName[], int numLines);
FILE* StartDump(const time_t seconds = time(NULL));
bool EndDump(FILE* file, const time_t timeS);
bool SmartPrintText(const char text[], FILE* file, int lenght);
bool swap(void* a, void* b);
bool BubbleSort(char** text, int(*compare)(const char str1[], const char str2[]), int N);
//bool BubbleSort(char** text, int(*compare)(const void* str1, const void* str2), int N);
int Min(const int a, const int b);
int strcmpend(const void* a, const void* b);
void mystring_desctor(mystring *This);
void mystring_ctor(mystring *This, const char* str);
inline bool IsLetter(char s);

bool dump = 1;
enum method {bubble, quick};

int main()
{
	printf("# -OneginSearch- \n");
	setlocale(LC_ALL, "Russian");
	time_t timeS;
	method SortMode = bubble;
	char InputName1[11] = "onegin.txt";
	char OutputName1[24] = "OneginSortFromBegin.txt";
	char OutputName2[22] = "OneginSortFromEnd.txt";

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
	if (fInput == nullptr) return perror("Error"),1;

	int lenght = Lenght(fInput);
	if (lenght < 0) return perror("Error"), 1;
	if (dump) fprintf(dumpFile, "Size of file: %d\n", lenght);

	char* buffer = (char*)calloc(lenght, sizeof(*buffer));
	if (buffer == nullptr) return perror("Error"), 1;

	int numOfWasRead = (fread_s(buffer, lenght, sizeof(char), lenght, fInput));
	if (dump) fprintf(dumpFile, "Number of read symbols: %d\n", numOfWasRead);
	if(numOfWasRead != lenght) return perror("Error"), 1;
	fclose(fInput);

	if (dump) SmartPrintText(buffer, dumpFile, lenght);

	int numOfLines = countNumberOfLines(buffer, lenght);
	assert(numOfLines > 0);

	char** linesArray = (char**)calloc(numOfLines, sizeof(int));
	if (linesArray == nullptr) return perror("Error"), 1;
	if (dump) fprintf(dumpFile, "sizeof(linesArray): %d\nNumber of Lines: %d\n",
		sizeof(linesArray),numOfLines);

	CreateStringArray(buffer, lenght, numOfLines, linesArray);

	if (SortMode) BubbleSort(linesArray, *strcmp, numOfLines);
	else qsort(linesArray, numOfLines, sizeof(linesArray[0]), strcmpbegin);
	Write(linesArray, OutputName1, numOfLines);
	if (errno) return perror("Error"), 1;
	
	mystring* stringesArray = (mystring*)calloc(numOfLines,sizeof(stringesArray[0]));
	for (int i = 0; i < numOfLines; ++i)
	{
		mystring_ctor(&stringesArray[i], linesArray[i]);
	}

	qsort(stringesArray, numOfLines, sizeof(stringesArray[0]), strcmpend);
	Write(stringesArray, OutputName2, numOfLines);
	if (errno) return perror("Error"), 1;

	free(buffer);
	buffer = NULL;
	free(linesArray);
	linesArray = NULL;

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

int countNumberOfLines(char buf[], int len)
{
	if (buf == nullptr) return -1;

	int count = 1;
	for (int i = 0; i < len; i++)
		if (buf[i] == '\n') count++;
	return count;
}

int CreateStringArray(char buf[], int len, int numLines, char *line[])
{
	if (buf == nullptr || line == nullptr) return -1;

	int beginOfString = 0, j = 0;
	for (int i = 0; i < numLines-1; ++i, ++j)
	{
		line[i] = buf + j;
		while (j++ < len && buf[j] != '\n') ;
		buf[j] = '\0';
	}
	line[numLines-1] = buf + j;
	return 0;
}

inline int strcmpbegin(const void* a, const void* b)
{
	return strcmp(*(const char**)a, *(const char**)b);
}

int Write(char *line[], char fileName[], int numLines)
{
	if (line == nullptr) return -1;

	FILE *fOutput = fopen(fileName, "w");
	if (fOutput == nullptr) return 1;
	for (int i = 0; i < numLines; i++)
		fprintf(fOutput, "%s\n", line[i]);
	fclose(fOutput);
	return 0;
}

int Write(mystring line[], char fileName[], int numLines)
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
	fprintf(file, "%s\nElapsed time: %d\n------------END------------", strerror(errno), elTime);
	fclose(file);
	return 0;
}

bool SmartPrintText(const char text[], FILE* file, int lenght)
{
	const char carriage = 39, enter = 35, end = 36;

	fprintf(file, "*****************\n0.0 ");

	int numOfLines = 1;
	for (int i = 0; i < lenght; ++i)
	{
		if (text[i] == '\n')
		{
			fprintf(file, "%c\n%d.%d ", enter, numOfLines, i); ++numOfLines;
		}
		else if (text[i] == '\r') fprintf(file, "%c", carriage);
		else if (text[i] == '\0') fprintf(file, "%c", end);
		else fprintf(file, "%c", text[i]);
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
				swap((void*)text[i], (void*)text[j]);
	return 0;
}

//bool BubbleSort(char** text, int(*compare)(const void* str1, const void* str2), int N)
//{
//	if (text == nullptr || N < 0)
//	{
//		errno = EINVAL;
//		return 1;
//	}
//	for (int i = 0; i < N; ++i)
//		for (int j = 0; j < N - 1; ++j)
//			if (compare(text[i], text[j]) < 0)
//				swap((void*)text[i], (void*)text[j]);
//	return 0;
//}

inline bool swap(void* a, void* b)
{
	void* c = a;
	b = a;
	a = c;
	return 0;
}

inline int strcmpend(const void* a, const void* b)
{
	const mystring* a2 = (mystring*)a;
	const mystring* b2 = (mystring*)b;
	int min = Min((a2)->len, b2->len);
	for (int i = min - 2, j = min - 2; i && j; --i, --j)
	{

		//if (!IsLetter(a2->str[i]))
		//{
		//	--j;
		//	continue;
		//}
		//if (!IsLetter(b2->str[j]))
		//{
		//	--i;
		//	continue;
		//}
		if (a2->str[i] > b2->str[j]) return 1;
		if (a2->str[i] == b2->str[j]) return 0;
		return -1;
	}
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

inline bool IsLetter(char s)
{
	if (s >= 65 && s <= 89 || s >= 97 && s <= 122 || s >= 128 && s <= 175 || s >= 224 && s <= 247) return 1;
	else return 0;
}