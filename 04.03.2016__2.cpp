#include <iostream>
#include <cassert>

using std::cout;
using std::endl;

class Array
{
private:
	int *mass;
	int SizeOfArr;
public:
	Array(int *m, int size)
	{
		SizeOfArr = size;
		mass = new int[SizeOfArr];
		for (int i = 0; i < size; i++)
			mass[i] = m[i];
	}
	int get_size() const
	{
		return SizeOfArr;
	}
	int *get_data() const
	{
		return mass;
	}
	int operator[](int i)
	{
		assert(i >= 0);
		return mass[i];
	}
	Array& operator=(const Array & obj)
	{
		if (this == &obj)
            return *this;
  
		SizeOfArr = obj.get_size();
		mass = new int[SizeOfArr];
		int *OldMass = obj.get_data();
		for (int i = 0; i < SizeOfArr; i++)
			mass[i] = OldMass[i];
		return *this;
	}
	bool operator==(const Array & obj)
	{
		if (SizeOfArr != obj.get_size())
			return 0;
		int *OldMass = obj.get_data();
		for (int i = 0; i < SizeOfArr; i++)
			if (OldMass[i] != mass[i])
				return 0;
		return 1;

	}
	~Array()
	{
		delete [] mass;
	}
	
};

int main()
{
	int Mass1[5] = {0, 1, 2, 3, 4};
	int Mass2[5] = {5, 6, 7, 8, 9};
	Array obj1 = Array(Mass1, 5);
	Array obj2 = Array(Mass2, 5);
	cout << obj1[3] << ' ' << obj2[3] << endl;
	Array obj3 = Array(NULL, 0);
	obj3 = obj2;
	if ((obj3 == obj2) && !(obj1 == obj2))
		cout << "right ;)" << endl;
	else
		cout << "sadness :(" << endl;

}
