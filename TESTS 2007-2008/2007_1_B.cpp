#include <iostream>
#include <cerrno>
#include <cmath>
#include <assert.h>
using std::cout;
using std::cin;

int SmartInput(const char name[], const int bound1 = INT_MIN, const int bound2 = INT_MAX);
bool CheckQuadraticDivider (int Num);

int main()
{
	cout << "# Test 2007.1.B -CheckQuadraticDivider-\n";

	int N = SmartInput("N", 0);
	if (errno) return perror("Input Error"), 1;
	if(CheckQuadraticDivider(N)) cout << "YES\n";
	else cout << "No\n";
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

bool CheckQuadraticDivider(int Num)
{
	assert(Num >= 0);
	for (int i = 2; i <= sqrt(Num); ++i)
		if (Num % (i*i) == 0)
			return true;
	return false;
}