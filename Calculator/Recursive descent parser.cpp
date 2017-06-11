#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <locale>
#include <ctime>
#include <cerrno>


#define it_says(a,type) if(Dump) fprintf(DumpFile, "%s: "#a" = %"#type"\n", __func__, a)
#define it_says_pointer(a,type) if(Dump) fprintf(DumpFile, "%s: "#a" = %d ; *"#a" = %"#type"\n", __func__, a, *##a)
#define hi  if (Dump) fprintf(DumpFile, "%s {\n", __func__)
#define bye if (Dump) fprintf(DumpFile, "%s }\n", __func__)

char* s;
FILE* DumpFile = nullptr;
bool Dump = true;

int GetG0(const char*str);

int GetE(); // E := T(['*''/']T)*

int GetT(); // T := P(['*''/']P)*

int GetP(); // P := '('E')' | E

int GetN(); // N := ['0'-'9']+

bool StartDump(const time_t seconds);
bool EndDump(const time_t timeS);

int main()
{
	//const char string[] = "123+17-5*72+(1-1)*(1111111113)";
	const char string[100] = {};
	time_t timeS = 0;
	
	scanf("%s", string);

	if (Dump)
	{
		timeS = time(NULL);
		StartDump(timeS);
		if (DumpFile == nullptr)
		{
			Dump = 0;
			printf("Can't create dump_file");
		}
	}

	int answer = GetG0(string);
	printf("%d\n", answer);

	if (Dump) fprintf(DumpFile, "ANSWER = %d\n", answer);
	EndDump(timeS);
	return 0;
}

int GetG0(const char*str)
{
//if (Dump) fprintf(DumpFile,"{ Hello, My name is GetG0. Glad to meet you\n");
	hi;

	s = (char*)str;

	it_says_pointer(s, c);
	
	int val = GetE();
	
	it_says(val, d);

	assert(*s == 0);

	bye;
	return val;
}

int GetE() // E := T(['*''/']T)*
{
	hi;

	int val = GetT();

	it_says(val, d);

	while (*s == '+' || *s == '-')
	{
		int op = *s++;
		val = (op == '+') ? (val + GetT()) : (val - GetT());

		it_says_pointer(s, c);
		it_says(val, d);
	}

	bye;
	return val;
}

int GetT() // T := P(['*''/']P)*
{
	hi;

	int val = GetP();

	it_says(val, d);

	while (*s == '*' || *s == '/')
	{
		int op = *s++;
		val = (op == '*') ? (val * GetP()) : (val / GetP());
		
		it_says_pointer(s, c);
		it_says(val, d);
	}

	bye;
	return val;
}

int GetP() // P := '('E')' | E
{
	hi;

	if (*s == '(')
	{
		++s;

		it_says_pointer(s, c);

		int val = GetE();

		it_says(val, d);

		assert(*s++ == ')');

		it_says_pointer(s, c);

		bye;

		return val;
	}
	else
	{
		int val = GetN();
		bye;
		return val;
	}
}

int GetN() // N := ['0'-'9']+
{
	hi;

	int val = 0;
	it_says(val, d);

	while ('0' <= *s && *s <= '9')
	{
		val = val * 10 + *s - '0';
		it_says(val, d);
		s++;
		it_says_pointer(s, d);
	}
	
	bye;
	return val;
}

bool StartDump(const time_t seconds)
{
	DumpFile = fopen("~ULTRA_SWAG_DOGE_dump.txt", "a");
	tm* timeinfo = localtime(&seconds);
	fprintf(DumpFile, "%s\n", asctime(timeinfo));
	return 0;
}

bool EndDump(const time_t timeS)
{
	long int elTime = time(NULL) - timeS;
	fprintf(DumpFile, "%s\nElapsed time: %d seconds\n------------END------------\n\n", strerror(errno), elTime);
	fclose(DumpFile);
	return 0;
}