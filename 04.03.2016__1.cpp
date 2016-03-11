#include <iostream>
#include <cstring>

using std::cout;
using std::endl;

class String
{
private:
	char *str;
	int string_size;
public:
	String(char *s)
	{
		assert(s);
		string_size = strlen(s);
		str = new char[string_size];
		strcpy(str, s);
	} 
	const int get_size() const
	{
		return string_size;
	}
	const char *get_str() const
	{
		return str;
	}
	String operator+(const String & s)
	{
		int n = s.get_size();
		int new_size = n + string_size + 1;
		char *new_str = new char[new_size];
		strcpy(new_str, str);
		const char *str2 = s.get_str();
		for(int i = 1; i <= n + 1; i++)
			new_str[string_size + i - 1] = str2[i - 1];
		return (String(new_str));
	}
	~String()
	{
		delete [] str;
	}
};

int main()
{
	String MyStr1 = String("Hello, ");
	String MyStr2 = String("world!\n");
	String sum = MyStr1 + MyStr2;
	cout << sum.get_str() << endl;
	return 0;
}
