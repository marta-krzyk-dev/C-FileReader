#include "stdafx.h"
#include "FileReader.h"
#include <string>



using namespace std;

int main()
{
	FileReader fr("...\\data.txt");

	bool b = fr.Read<bool>();
	bool b2 = fr.Read<bool>();
	short sh = fr.Read2<short>();
	unsigned short us = fr.Read2<unsigned short>();
	int i = fr.Read2<int>();
	unsigned int ui = fr.Read2<unsigned int>();
	long l = fr.Read2<long>();
	long long ll = fr.Read2<long long>();
	float f = fr.Read2<float>();
	double d = fr.Read2<double>();
	char c = fr.Read2<char>();
	string s = fr.Read2<string>();
	
	cout << b << endl;
	cout << b2 << endl;
	cout << sh << endl;
	cout << us << endl;
	cout << i << endl;
	cout << ui << endl;
	cout << l << endl;
	cout << ll << endl;
	cout << f << endl;
	cout << d << endl;
	cout << c << endl;
	cout << "*" << s << "*" << endl;
	cout << "*" << fr.Read2<string>() << "*" << endl;
	cout << "*" << fr.Read2<string>() << "*" << endl;

	system("pause");

	return 0;
}
