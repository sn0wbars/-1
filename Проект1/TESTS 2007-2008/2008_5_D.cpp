#include <iostream>
#include <cerrno>
#include <assert.h>
using std::cout;
using std::cin;

int SmartInput(const char name[], const int bound1 = INT_MIN, const int bound2 = INT_MAX);
bool Expansion(int arr[], int n, int k, int i);

int main()
{
	cout << "# Test 2008.5.D -Generation of expansion- \n";

	int N = SmartInput("N", 0, 31);
	int* array = new int[N+1];
	for (int i = 0; i <= N; i++) 
		array[i] = 0;
	Expansion(array, N, N, 0);
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

bool Expansion(int arr[], int n, int k, int i)
{
	if (n < 0) return 0;
	if (n == 0)
	{
		for (int j = 0; j < i; ++j)
		{
			cout << arr[j] << ' ';
		}
		cout << std::endl;
	}
	else 
	{
		if (n - k >= 0)
		{
			arr[i] = k; 
			Expansion(arr, n - k, k, i + 1);
		}
		if (k - 1 > 0)
		{
			Expansion(arr, n, k - 1, i);
		}
	}
	return 0;
}