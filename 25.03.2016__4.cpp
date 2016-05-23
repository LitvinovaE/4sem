#include <iostream>
#include <array>
#include <cstring>

#define KEY_WORD "programming"
#define ATTEMPTS 5

using std::cout;
using std::endl;

int main()
{
	typedef std::array<int, strlen(KEY_WORD)> MyArray;
	MyArray Word;
	int size = strlen(KEY_WORD);
	char str[size] = KEY_WORD;
	size--;
	MyArray::iterator it = Word.begin();
	for (int i = 0; i < size; i++)
	{
		Word[i] = 0;
	}
	int mistakes = 0;
	int correct = 0;
	char a;
	while((mistakes < ATTEMPTS) && (size != correct))
	{
		for (int i = 0; i <= size; i++)
			if (Word[i])
				cout << str[i];
			else
				cout << '-';
		cout << endl;
		cout << "mistakes " << mistakes  << " (max " << ATTEMPTS << ")" << endl;
		cout << "Enter a new letter:" << endl;
		std::cin >> a;
		int f = 0;
		for (int i = 0; i <= size; i++)
			if (str[i] == a)
			{
				Word[i] = 1;
				f = 1;
			}
		if (f == 0)
			mistakes++;
	}
	if (size == correct)
		cout << "Congratulations! You win!!" << endl;
	
	if (mistakes == ATTEMPTS)
		cout << "You lose!!  =(" << endl;
	//cout << Word[1] << Word[3] << endl;

	return 0;
}