// FUPM 571 Borzilov Alexander

#include <iostream>
#include <assert.h>
using std::cout;
using std::cin;

int main()
{
	cout << "# Test 2007.4.B -SymbolFilter-\n";
	char symbol = cin.get();
	bool flag = 1;
	bool space2 = 0;
	while (symbol)
	{
		bool space1 = space2;
		if (symbol == ' ' || symbol == '\t') space2 = 1;
		else space2 = 0;
		if (ispunct(symbol) || (space1 && space2)) flag = 0;
		if (symbol >= 'A' && symbol <= 'Z') symbol += 32;
		if (isdigit(symbol)) symbol = '#';
		if (flag) cout.put(symbol);
		symbol = cin.get();
		flag = 1;
	}
	return 0;
}

