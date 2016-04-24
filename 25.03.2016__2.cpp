#include <iostream>
#include <array>
#include <fstream>
#include <string>
#include <cstdio>

using std::cout;
using std::endl;
using std::array;

int main(int argc, char **argv)
{
	std::ifstream fin(argv[1]);
	if (!fin)
	{
		cout << "I couldn't open this file!" << endl;
		return 0;
	}

	array<int, 26> Symbols;
	for (int i = 0; i < 26; i++)
		Symbols[i] = 0;
	
	char c = 0;
	while(!fin.eof())
	{
		fin >> c;
		if (!isalpha(c))
			continue;
		else
		{
			c = towlower(c);
			Symbols[c - 'a'] = 1;
		}
	}

	for(int i = 0; i < 26; i++)
	{
		if(!Symbols[i])
			cout << char('a' + i) << ' ';
	}
	cout << endl;

	fin.close();
	return 0;
}