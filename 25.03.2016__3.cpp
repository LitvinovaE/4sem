#include <iostream>
#include <map>
#include <fstream>
#include <cstring>

using std::cout;
using std::endl;

char *read(char *buf)
{
	int size = strlen(buf) + 1;
	char *word = new char[size];
	for (int i = 0; i < size; i++)
	{
		if (!isalpha(buf[i]) && (buf[i] != '-'))
		{
			word[i] = '\0';
			break;
		}
		else
		{
			if(buf[i] != '-')
				buf[i] = towlower(buf[i]);
			word[i] = buf[i];
		}
	}
	return word;
}

int main()
{
	typedef std::map<std::string, int> MyMap;

	std::ifstream file("text.txt");
	if (!file)
	{
		cout << "I couldn't open this file!" << endl;
		return 0;
	}

	char buf[50];
	MyMap CollectWords;
	MyMap::iterator it;
	while (!file.eof())
	{
		file >> buf;
		if (*buf == '\0')
			continue;
		char *word = read(buf);
		if (*word == '\0')
			continue;
		*buf = '\0';
		if (CollectWords.empty())
			CollectWords.insert(std::pair<std::string, int>(word, 1));
		else
		{
			it = CollectWords.find(word);
			if (it != CollectWords.end())
				it->second++;
			else
				CollectWords.insert(std::pair<std::string, int>(word, 1));
		}
	}

	int size = CollectWords.size();
	if (size)
	{
		it = CollectWords.begin();
		while(it != CollectWords.end())
		{
			cout << it->first << " - " << it->second << endl;
			it++;
		}
	}
	else
		cout << "There are no words in this file." << endl;

	file.close();
	return 0;
}