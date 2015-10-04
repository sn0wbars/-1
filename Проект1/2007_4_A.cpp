// FUPM 571 Borzilov Alexander

#include <iostream>
#include <cerrno>
#include <cmath>
#include <assert.h>
using std::cout;
using std::cin;

unsigned int SmartInput(const char name[], const int bound1 = INT_MIN, 
	const int bound2 = INT_MAX);
unsigned long long int GCD(unsigned long long int a, unsigned long long int b);
unsigned long long int LCM(unsigned long long int a, unsigned long long int b);

int main()
{
	cout << "# Test 2007.4.A -lcmOfThreeNumbers-\n";

	unsigned int a = SmartInput("a", 0);
	unsigned int b = SmartInput("b", 0);
	unsigned int c = SmartInput("c", 0);
	if (errno) perror("Error"), 1;
	cout << LCM(LCM(a, b), c);
	return 0;
}

unsigned int SmartInput(const char name[], const int bound1, const int bound2)
{
	unsigned int val = 0;
	cout << "# Input " << name << "; " << bound1 << " < " << name << " < " <<
		bound2;
	for (int i = 0; i < 2; ++i)
	{
		cout << "\n>";
		if (!(cin >> val))
		{
			cin.clear();
			while (cin.get() != '\n');
		}
		if (val > bound1 && val < bound2)
			return val;
		cout << "# Invalid number";
	}
	errno = ERANGE;
	return 0;
}

unsigned long long int GCD(unsigned long long int a, unsigned long long int b)
{
	assert(a >= 0 && b >= 0);
	while (a && b)
		if (a > b) 
			a %= b; 
		else b %= a;
	return a + b;
}

unsigned long long int LCM(unsigned long long int a, unsigned long long int b)
{
	assert(a >= 0 && b >= 0);
	return a / GCD(a, b) * b;
}
