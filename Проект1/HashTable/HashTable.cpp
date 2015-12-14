#include "platypus.h"

#include <string.h>
#include "list.h"
#include "stack.h"
#include <ctime>
#include <locale>

const char Version[] = "1.0";
const int HASH_TABLE_SIZE = 509;
const int MAX_WORD_SIZE = 64;
bool DUMP = 1;
FILE* DUMPFile = NULL;
time_t timeS = 0;

void EndDump();
void StartDump();
bool SmartPrintText(const char text[], FILE* file, int lenght);
void print_help();
inline size_t HashStupid(const char word[]);
inline size_t HashFirstLtr(const char word[]);
inline size_t HashLenght(const char word[]);
inline size_t HashSum(const char word[]);
inline size_t HashSumCode(const char word[]);
inline size_t HashXor(const char word[]);

struct HashTable
{
	List<char*> Table[HASH_TABLE_SIZE];
	size_t(*HashFunc)(const char[]);
};

int main(int argc, char* argv[])
{
	timeS = time(NULL);

	setlocale(LC_ALL, "Netherlands");

	HashTable hashTable;
	hashTable.HashFunc = HashXor;

	char InputName[MAX_FILE_NAME] = {}, OutputName[MAX_FILE_NAME] = {};
	switch (argc)
	{
	case 1:
		strcpy(InputName, "data.txt");
		strcpy(OutputName, "data.csv");
		break;
	case 2:
		if (strcmp(argv[1], "--version") == 0)
		{
			printf("Version: %s", Version);
			return 2;
		}
		if (strcmp(argv[1], "--help") == 0)
		{
			print_help();
			return 1;
		}
		strcpy(InputName, argv[1]);
		strcat(InputName, ".txt");
		strcpy(OutputName, argv[1]);
		strcat(OutputName, ".csv");
		break;
	case 3:
		strcpy(InputName, argv[1]);
		strcat(OutputName, ".txt");
		strcpy(OutputName, argv[2]);
		strcat(OutputName, ".csv");
		break;
	default:
		print_help();
		return 1;
	}


	if (DUMP)
	{
		StartDump();
		if (DUMPFile == nullptr)
		{
			DUMP = 0;
			printf("Can't create dump_file");
		}
	}

	FILE* fInput = fopen(InputName, "rb");
	if (fInput == nullptr) return perror("Can't open Input file \nErrno"), 3;

	FILE* fOutput = fopen(OutputName, "wb");
	if (fOutput == nullptr) return perror("Can't open Output file\nErrno"), 4;

	const int lenght = Lenght(fInput);
	if (lenght < 0) return perror("Negative lenght of file\nErrno"), 1;
	if (DUMP) fprintf(DUMPFile, "Size of file: %d\n", lenght);

	char* buffer = (char*)calloc(lenght, sizeof(*buffer));
	if (buffer == nullptr) return perror("Can't create buffer\nErrno"), 1;

	const int numOfWasRead = (fread_s(buffer, lenght, sizeof(char), lenght, fInput));
	if (DUMP) fprintf(DUMPFile, "Number of read symbols: %d\n", numOfWasRead);
	if (numOfWasRead != lenght) return perror("Number of read symbols isn't equal lenght of file\nErrno"), 1;
	fclose(fInput);

	if (DUMP)
		if (SmartPrintText(buffer, DUMPFile, lenght))
		{
			printf("Dump error, cant print text");
			DUMP = 0;
		}

	
	Stack words;
	Stack_ctor(&words);
	for (int i = 0; i < lenght && buffer[i]; ++i)
	{
		if (isalnum((unsigned char)buffer[i]))
		{
			char* word = &buffer[i];

			while (isalnum((unsigned char)buffer[i]))
			{
			//	if (DUMP) printf("%d ", i);
				++i;
			}
			buffer[i] = 0;

			if (DUMP) if (i < 1000) printf("%s\n", word);
			size_t hash = hashTable.HashFunc(word);
			int shortHash = hash % HASH_TABLE_SIZE;
			if (hashTable.Table[shortHash].isfstnull())
				hashTable.Table[shortHash].pop();
			hashTable.Table[shortHash].push(word);
		}
	}

	if (DUMP) printf("Hash Table was created");
	for (int i = 0; i < HASH_TABLE_SIZE; ++i)
	{
		int numCollisions = 0;
		if (!hashTable.Table[i].isfstnull())
		numCollisions = hashTable.Table[i].getLen();
		fprintf(fOutput, "%d;", numCollisions);
	}

	long int elTime = time(NULL) - timeS;
	fprintf(fOutput, "\n%d", elTime);
	free(buffer);
	buffer = NULL;
	if (DUMP) EndDump();

	return 0;
}

inline size_t HashStupid(const char word[])
{
	assert(word);
	return 0;
}

inline size_t HashFirstLtr(const char word[])
{
	assert(word);
	return (size_t)word[0];
}

inline size_t HashLenght(const char word[])
{
	assert(word);
	return (size_t)strlen((char*)word);
}

inline size_t HashSum(const char word[])
{
	assert(word);
	size_t hash = 0;
	for (int i = 0; word[i]; ++i)
		hash += word[i];
	return hash;
}

inline size_t HashSumCode(const char word[])
{
	assert(word);
	return (HashSum(word) / HashLenght(word));
}

inline size_t HashXor(const char word[])
{
	assert(word);
	size_t hash = (size_t)word[0];

	for (int i = 1; word[i]; ++i)
	{
		*(char*)(&hash) ^= word[i];
		hash = (hash >> 1) | (hash << (sizeof(size_t) * 8 - 1));
	}
	return hash;
}


void print_help()
{
	printf("This is HashTable. is a data structure used to implement\
an associative array, a structure that can map keys to values.\n\
Keys:\n\
--help   Print help\n\
--version   Print version\n\
It should be zero or one or two parameters with no more than 32 symbols each\n\
Parametres:\n\
1. NAME_OF_INPUT_FILE //(default: data.txt)\n\
2. NAME_OF_OUTPUT_FILE //(default: data.csv)\n\
Input file has to have .txt expansion\n\
Output file has to have .csv expansion\n"
);
};


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

void StartDump()
{
	DUMPFile = fopen("Hash_table.dmp", "w");
	tm* timeinfo = localtime(&timeS);
	fprintf(DUMPFile, "%s\n", asctime(timeinfo));
}

void EndDump()
{
	long int elTime = time(NULL) - timeS;
	fprintf(DUMPFile, "%s\nElapsed time: %d seconds\n------------END------------", strerror(errno), elTime);
	fclose(DUMPFile);
}