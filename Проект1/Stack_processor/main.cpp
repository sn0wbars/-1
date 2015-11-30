#include "platypus.h"
#include "CPU.h"
#include <string.h>

const char name_def[] = "code.bin";

int main(int argc, char* argv[])
{
	char InputName[32] = {};
	switch (argc)
	{
	case 1:
		strcpy(InputName, name_def);
		break;
	case 2:
		if (strcmp(argv[1], "--help") == 0)
		{
			return 1;
		}
		strcpy(InputName, argv[1]);
		break;
	default:
		return 1;
	}
	Cpu processor;
	Cpu_ctor(&processor, 256);
	Cpu_OK(&processor);

	char programm[MAX_PROGRAM_SIZE] = {};

	FILE* fInput = fopen(InputName, "rb");
	if (errno) return perror("Can't open file\nErrno"), 1;

	const int lenght = Lenght(fInput);
	if (lenght < 0) return perror("Negative lenght of file\nErrno"), 1;

	const int numOfWasRead = fread(programm, sizeof(char), lenght, fInput);
	if (numOfWasRead != lenght) return perror("Number of read symbols isn't equal lenght of file\nErrno"), 1;

	if (DUMP_ON) for (int i = 0; i < lenght; ++i) printf("%d ", programm[i]);
	if (errno) return perror("Can't read file\nErrno"), 1;

	Cpu_exe(&processor, programm);
	return 0;
}