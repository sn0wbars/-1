//todo: переделать алгоритм
#include <iostream>
#include <cerrno>
#include <assert.h>
using std::cout;
using std::cin;

int SummOf4Squares(int num);
int SmartInput(const char name[], const int bound1 = INT_MIN, const int bound2 = INT_MAX);
bool IsInt(double num);

int main()
{
	cout << "# Test 2008.5.C -Summ of 4 squares- \n";

	int N = SmartInput("N", 0, 2000001);
	if (errno) return perror("Input error"), 1;
	SummOf4Squares(N);
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

int SummOf4Squares(int number)
{
	assert(number >= 0);
	int num = number;
	for (num; num; --num)
	{
		if (IsInt(sqrt(num)))
		{
			cout << num << ' ';
			SummOf4Squares(number - num);
			return 0;
		}
	}
	return 0;
}

inline bool IsInt(double num)
{
	return ((num)-(int)num == 0);
}