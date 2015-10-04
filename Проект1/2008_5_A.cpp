#include <iostream>
#include <cerrno>
#include <assert.h>
using std::cout;
using std::cin;

int SmartInput(const char name[], const int bound1 = INT_MIN, const int bound2 = INT_MAX);
int SummOfDigits(int num);

int main()
{
	cout << "# Test 2008.5.A -Summ of Digits- \n";

	int N = SmartInput("N", -1);
	if (errno) return perror("Input error"), 1;
	cout << SummOfDigits(N);
	system("pause");
	return 0;
}

int SmartInput(const char name[], const int bound1, const int bound2)
{
	int val = 0;
	cout << "# Input " << name << "; " << bound1 << " < " << name << " < " <<
		bound2;
	for (int i = 0; i < 20; ++i)
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

int SummOfDigits(int num)
{
	assert(num>=0);
	int summ = 0;
	while (num)
	{
		summ += num % 10;
		num /= 10;
	}
	return summ;
}