// FUPM 571 Alexander Borzilov
#include <iostream>
#include <assert.h>
#include <cerrno>
using std::cin;
using std::cout;

int SmartInput(const char name[], const int bound1 = INT_MIN, const int bound2 = INT_MAX);
int NumOfExpansWOrepeat(int arr[][500], int n, int k);

int arr[500][500];

int main()
{
	cout << "# Test 2007.4.D -NumberOfExpansions- \n";
	int arr[500][500];
	for (int i = 0; i < 500; ++i)
		for (int j = 0; j < 500; ++j)
			arr[i][j] = -1;
	int N = SmartInput("N", 0, 500);
	cout << NumOfExpansWOrepeat(arr, N, N);
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

int NumOfExpansWOrepeat(int arr[][500], int n, int k)
{
	if (n == 0) return 1;
	if (n < 0) return 0;
	if (k < 1) return 0;
	if (arr[n][k] >= 0) return arr[n][k];
	arr[n][k] = NumOfExpansWOrepeat(arr, n, k - 1) + NumOfExpansWOrepeat(arr, n - k, k - 1);
	return arr[n][k];
}
