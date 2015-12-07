#include "platypus.h"
#include <string.h>

const char Version[] = "1.2";

void print_help();
void print_error(FILE* fOutput, char name[]);

bool asm_push(FILE* fInput, FILE* fOutput);
bool asm_jump(FILE* fInput, FILE* fOutput);

int main(int argc, char* argv[])
{
	char InputName[MAX_FILE_NAME] = {}, OutputName[MAX_FILE_NAME] = {};
	switch (argc)
	{
	case 1:
		strcpy(InputName, "programm.txt");
		strcpy(OutputName, "code");
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
		strcpy(OutputName, argv[1]);
		break;
	case 3:
		strcpy(InputName, argv[1]);
		strcpy(OutputName, argv[2]);
		break;
	default:
		print_help();
		return 1;
	}
	strcat(OutputName, ".bin");

	FILE* fInput = fopen(InputName, "rb");
	if (fInput == nullptr) return perror("Can't open Input file \nErrno"), 3;

	FILE* fOutput = fopen(OutputName, "wb");
	if (fOutput == nullptr) return perror("Can't open Output file\nErrno"), 4;

	char str[MAX_LENGTHofCOMMAND] = {};

	//int NumCommand = -1; 
	if (!fscanf(fInput, "%s", str)) return perror("Can't read file\nErrno"), 5;
	if (strcmp(str, SIGNATURE))
	{
		printf("Wrong Signature\n");
		return 6;
	}
	if (!fscanf(fInput, "%s", str)) return perror("Can't read file\nErrno"), 5;

	if (strcmp(str, Version))
	{
		printf("Incompatible versions\n");
		return 7;
	}

	while (fscanf(fInput, "%s", str) != EOF)
	{
		if (DUMP_ON) printf("%s ", str);
		#define DEF_CMD(name, num, code, codeAsm, codeDisasm)\
		if(_stricmp(str, #name) == 0)\
		{\
				fprintf(fOutput,"%c", num);\
				codeAsm;\
		}\
		else 

		#include "CmdList.h"
		
		if (str[0] == ':')
		{
			fscanf(fInput, "%s", str);
		}
		else
		{
			printf("Error: Unknown command\n");
			fprintf(fOutput, "[Unknown command] ");
		}
	}

	fclose(fInput);
	fclose(fOutput);
	printf("Programm was written into %s.\n", OutputName);

	return 0;
}

bool asm_jump(FILE* fInput, FILE* fOutput)
{
	char mark[MAX_LENGTHofCOMMAND] = {};
	char string[MAX_LENGTHofCOMMAND] = {};

	fscanf(fInput, "%s", &mark);
	long int position = ftell(fInput);
	unsigned int numCommand = -2; // numeration from 0. -2, because of signature and version

	fseek(fInput, 0, SEEK_SET);
	while (fscanf(fInput, "%s", string) != EOF)
	{
		if (string[0] == ':')
		{
			fscanf(fInput, "%s", string);
			if (strcmp(string, mark) == 0)
			{
				fprintf(fOutput, "%c", numCommand);
				fseek(fInput, position, SEEK_SET);
				return 1;
			}
		}
		else ++numCommand;
		if (_stricmp(string, "PUSH") == 0) numCommand += SIZEofTYPEofNUMBERS - 1;
		if (errno) return print_error(fOutput, "jump"), 0;
	}
	return 0;
}

bool asm_push(FILE* fInput, FILE* fOutput)
{
	TYPEofNUMBERS number = 0;
	if (SIZEofTYPEofNUMBERS == sizeof(int) || SIZEofTYPEofNUMBERS == sizeof(double))
	{
		if (SIZEofTYPEofNUMBERS == sizeof(int))
			fscanf(fInput, "%d", &number);
		else fscanf(fInput, "%f", &number);
		if (errno) return print_error(fOutput, "push"), 0;

		char bytes[SIZEofTYPEofNUMBERS] = {};
		memcpy(bytes, &number, SIZEofTYPEofNUMBERS);
		for (int i = 0; i < SIZEofTYPEofNUMBERS; ++i)
		{
			fprintf(fOutput, "%c", bytes[i]);
		}
		if (errno) return print_error(fOutput, "push"), 0;
	}
	else if (SIZEofTYPEofNUMBERS == sizeof(char))
	{
		fscanf(fInput, "%c", number);
		fprintf(fOutput, "%c", number);
		if (errno) return print_error(fOutput, "push"), 0;
	}
	else
	{
		printf("PUSH has wrong argument\n");
		fprintf(fOutput, "[ERROR]\n");
		return 0;
	}
	return 1;
};

void print_help()
{
	printf("This is assembler. It converts assembler code into machine code\n\
Keys:\n\
--help   Print help\n\
--version   Print version\n\
It should be zero or one or two parameters with no more than 32 symbols each\n\
Parametres:\n\
1. NAME_OF_INPUT_FILE.EXPANSION //(default: programm.txt)\n\
2. NAME_OF_OUTPUT_FILE //(default: code)\n\
Output file has to have .bin expansion\n"
);
};

void print_error(FILE* fOutput, char name[])
{
	printf("Error: %s has wrong argument\n", name);
	perror("Errno\n");
	fprintf(fOutput, "[ERROR] ERRNO: %d\n", errno);
}