#include "platypus.h"
#include <string.h>

const char Version[] = "1.1";

void print_help();
void print_error(FILE* fOutput, char name[]);

bool disasm_push(FILE* fInput, FILE* fOutput);
//bool asm_jump(FILE* fInput, FILE* fOutput);

int main(int argc, char* argv[])
{
	char InputName[32] = {}, OutputName[32] = {};
	switch (argc)
	{
	case 1:
		strcpy(InputName, "code");
		strcpy(OutputName, "programm.txt");
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

	char str = 0;

	while (fscanf(fInput, "%d", str) != EOF)
	{
		printf("%d ", str);
		#define DEF_CMD(name, num, code, codeAsm, codeDisasm)\
		if(str == num)\
		{\
				fprintf(fOutput, #name" ");\
				codeDisasm;\
				fprintf(fOutput, "\n");\
		}\
		else 

		#include "CmdList.h"

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

bool disasm_push(FILE* fInput, FILE* fOutput)
{
	TYPEofNUMBERS number = 0;
	char bytes[SIZEofTYPEofNUMBERS] = {};
	for (int i = 0; i < SIZEofTYPEofNUMBERS; ++i)
		fscanf(fInput, "%d", bytes[i]);
	if (errno) return print_error(fOutput, "push"), 0;

	fprintf(fOutput, "%d ", (*(TYPEofNUMBERS*)bytes));
	if (errno) return print_error(fOutput, "push"), 0;
	return 1;
};

void print_error(FILE* fOutput, char name[])
{
	printf("Error: %s has wrong argument\n", name);
	perror("Errno\n");
	fprintf(fOutput, "[ERROR] ERRNO: %d\n", errno);
}

void print_help()
{
	printf("This is disassembler. It converts machine code into assembler code\n\
Keys:\n\
--help   Print help\n\
--version   Print version\n\
It should be zero or one or two parameters with no more than 32 symbols each\n\
Parametres:\n\
1. NAME_OF_INPUT_FILE //(default: code)\n\
2. NAME_OF_OUTPUT_FILE.EXPANSION //(default: programm.txt)\n\
Intput file has to have .bin expansion\n"
);
};

bool disasm_jump(FILE* fInput, FILE* fOutput) { return 1; }