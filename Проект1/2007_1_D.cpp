#include <iostream>
#include <cerrno>
#include <assert.h>
using std::cout;
using std::cin;

int SmartInput(const char name[], const int bound1 = INT_MIN, const int bound2 = INT_MAX);
unsigned long long int** DynamicPascalTriangle(int x,int y);
void Print_with_alignment(unsigned long long int** array, int n);
//void cout_ign0(int num);

const int n_max = 47;

int main()
{
	cout << "# Test 2007.1.D -Table of amounts of good words- \n";

	int N = SmartInput("N", -1, n_max + 1);
	if (errno) return perror("Input Error"), 1;
	unsigned long long int **table = DynamicPascalTriangle(N+1, N);
	Print_with_alignment(table, N);
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

unsigned long long int** DynamicPascalTriangle(int y, int x)
{
	assert(x>=0  && y>= 0);
	unsigned long long int** matrix = new unsigned long long int*[y];
	for (int i = 0; i < y; i++)
	{
		matrix[i] = new unsigned long long int[x];
		matrix[i][0] = 1;
		for (int j = 0; j < x; ++j)
		{
			matrix[0][j] = 1;
			if (i && j) matrix[i][j] = matrix[i - 1][j] + matrix[i][j - 1];
		}				
	}
	return matrix;
}

void Print_with_alignment(unsigned long long int** array, int n)
{
	int otstup = 0, t = 1;
	//todo: добавить выравнивание по длине чисел
	for (int i = 0; i <= n; ++i)
	{
		if (t-- == 0)
		{
			t = ++otstup;
		}
		int temp = i;
		for (int j = 0; j <= otstup; ++j)
		{
			cout << (array[temp][j]);
			temp = temp - array[j][1];
			cout << ' ';
		}
		cout << std::endl;
	}
}

//inline void cout_ign0(int num)
//{
//	if (num) cout << num;
//	else cout << 0;
//}