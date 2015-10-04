#include <iostream>
#include <cerrno>
#include <assert.h>
using std::cout;
using std::cin;

int SmartInput(const char name[], const int bound1 = INT_MIN, const int bound2 = INT_MAX);
bool Weighing(int Num);

int main()
{
	cout << "# Test 2007.1.C -Weighing- \n";

	int N = SmartInput("N", 0);
	if (errno) return perror("Input error"), 1;
	if (Weighing(N)) cout << "YES";
	else cout << "NO";
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

bool Weighing(int Num)
{
	assert(Num >= 0);
	if (Num == 0 || Num == 1 || Num == 3) return true;
	int NumMod4 = Num % 4;
	if (NumMod4 == 3) NumMod4 -= 4;
	else if (NumMod4 == 2) return false;
	return Weighing((Num - NumMod4) / 4);
}