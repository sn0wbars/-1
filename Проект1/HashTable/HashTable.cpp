#include "platypus.h"

#include <string.h>
#include "list.h"
#include "stack.h"

const char Version[] = "1.0";
const int HASH_TABLE_SIZE = 509;
const int MAX_WORD_SIZE = 64;

void print_help();
inline size_t HashStupid(const char word[]);
inline size_t HashFirstLtr(const char word[]);
inline size_t HashLenght(const char word[]);
inline size_t HashSum(const char word[]);
inline size_t HashSumCode(const char word[]);
inline size_t hashXor(const char word[]);

struct HashTable
{
	List<char*> Table[HASH_TABLE_SIZE];
	size_t(*HashFunc)(const char[]);
};

int main(int argc, char* argv[])
{
	HashTable hashTable;
	hashTable.HashFunc = HashStupid;

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

	FILE* fInput = fopen(InputName, "rb");
	if (fInput == nullptr) return perror("Can't open Input file \nErrno"), 3;

	FILE* fOutput = fopen(OutputName, "wb");
	if (fOutput == nullptr) return perror("Can't open Output file\nErrno"), 4;

	const int lenght = Lenght(fInput);
	if (lenght < 0) return perror("Negative lenght of file\nErrno"), 1;

	char* buffer = (char*)calloc(lenght, sizeof(*buffer));
	if (buffer == nullptr) return perror("Can't create buffer\nErrno"), 1;

	const int numOfWasRead = (fread_s(buffer, lenght, sizeof(char), lenght, fInput));
	if (numOfWasRead != lenght) return perror("Number of read symbols isn't equal lenght of file\nErrno"), 1;
	fclose(fInput);


	Stack words;
	Stack_ctor(&words);
	Stack_push(&words, buffer);
	for (int i = 0; i < lenght; ++i)
		if (buffer[i] == ' ' || buffer[i] == '\n')
		{
			buffer[i] = 0;
			if (buffer[i + 1] != 0 || buffer[i + 1] != ' ')
				Stack_push(&words, &buffer[i + 1]);
		}
	printf("%s", buffer);
	char* str;
	while (Stack_pop(&words, &str))
	{
		size_t hash = hashTable.HashFunc(str);
		int shortHash = hash % HASH_TABLE_SIZE;
		if (hashTable.Table[shortHash].isfstnull())
		{
			hashTable.Table[shortHash].pop();
			hashTable.Table[shortHash].push(str);
		}
		hashTable.Table[shortHash].push(str);
	}
	for (int i = 0; i < HASH_TABLE_SIZE; ++i)
	{
		int numCollisions = hashTable.Table[i].getLen();
		fprintf(fOutput, "%d,", numCollisions);
	}

	free(buffer);
	buffer = NULL;
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
	return (size_t)strlen(word);
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

inline size_t hashXor(const char word[])
{
	assert(word);
	size_t hash = (size_t)word[0];

	for (int i = 1; word[i]; ++i)
	{
		hash = (char)hash ^ word[i];
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