#include <vector>
#include <iostream>

using std::cout;
using std::endl;
using std::vector;

int main(int argc, char **argv)
{
	vector<int> MyNums;
	for (int i = 1; i < argc; i++)
	{
		int num = 0;
		int k = 0;
		while (argv[i][k] != '\0')
		{
			num = num * 10 + (argv[i][k] - '0');
			k++;
		}
		k++;
		MyNums.push_back(num);
	}

	int size1 = MyNums.size();
	vector<int> Nums;
	Nums.push_back(MyNums[0]);
	int size2 = Nums.size();

	for (int i = 0; i < size1; i++)
	{
		int f = 0;
		for (int j = 0; j < size2; j++)
			if (MyNums[i] == MyNums[j])
				f = 1;
		if (!f)
		{
			Nums.push_back(MyNums[i]);
			size2 = Nums.size();
		}
	}
	cout << size2 << endl;
	return 0;
}