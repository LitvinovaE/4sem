#include <iostream>
#include <array>
#include <cstring>

#define KEY_WORD "programming"
#define ATTEMPTS 5

using std::cout;
using std::endl;

int main()
{
	std::array<int, strlen(KEY_WORD)> Word;
	int size = strlen(KEY_WORD);
	Word::iterator it = Word.begin();
	for (int i = 0; i < size; i ++)
	{
		Word[i] = 0;
	}
	int mistakes = 0;
	cout << Word[1] << Word[3] << endl;

	return 0;
}