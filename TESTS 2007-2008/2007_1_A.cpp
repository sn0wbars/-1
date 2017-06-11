#include <iostream>
#include <cerrno>
#include <cmath>
#include <assert.h>
using std::cout;
using std::cin;

const int maxAmount = 10000;
int SmartInput(const char name[], const int bound1 = INT_MIN, const int bound2 = INT_MAX);
int* DynamicInput(int size);
void PrintSimplFrArr(int* arr, int n);
bool IsSimple(int Num);

int main()
{
	cout << "# Test 2007.1.A -CheckSimpleNumbers-\n";

	int N = SmartInput("amount of numbers", 0, 10000);
	if (errno) return perror("Input Error"), 1;
	int* array = DynamicInput(N);
	if (errno)
	{
		delete[] array;
		return perror("Input Error"), 1;
	}
	PrintSimplFrArr(array, N);
	delete[] array;
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

int* DynamicInput(int size)
{
	int* arr = new int[size];
	for (int i = 0; i < size; ++i)
		arr[i] = SmartInput("number", 0, 100000);
	return arr;
}

inline void PrintSimplFrArr(int* arr, int n)
{
	for (int i = 0; i < n; ++i)
		if (IsSimple(arr[i])) cout << arr[i] << ' ';
}

bool IsSimple(int Num)
{
	assert(Num > 0);
	if (Num == 1) return true;
	for (int i = 2; i <= sqrt(Num); ++i)
		if (Num % i == 0) return false;
	return true;
}
