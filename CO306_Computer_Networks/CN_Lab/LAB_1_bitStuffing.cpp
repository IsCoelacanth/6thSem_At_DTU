#include<iostream>
#include<string>
using namespace std;

int main()
{
    int len, count;
	string S;
	cout << "Enter the bit sequence : ";
	cin >> S;
	len = S.length();

	for (int i = 0; i < len; i++)
	{
		count = 0;
		for (int j = i; j < (i + 5); j++)
		{
			if (S[j] == '1')
			{
				count++;
			}
		}
		if (count == 5)
		{
			int n1 = len + 2;
			for (; n1 > i+5 ; n1--)
			{
				S[n1] = S[n1 - 1];
			}
			S[i + 5] = '0';
			i += 6;
		}
	}

	cout << "The string after stuffing is : ";
	cout << "01111110 ";
	cout << S;
	cout << "01111110" << endl;
	return 0;
}
