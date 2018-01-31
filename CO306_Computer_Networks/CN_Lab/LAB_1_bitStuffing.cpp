/*
 To implement bit stuffing and destuffing
 This implementation is unrestricted in terms of the size
 of input sequence.
  */
#include<iostream>
#include<string>
using namespace std;

int main()
{
	int len, count = 0 ;
	string S;
	cout << "Enter the bit sequence : ";
	cin >> S;
	len = S.length();
	int i = 0;
	while ( i != S.length() )
	{
		
		if (S[i] == '0')
			count = 0;
		if (S[i] == '1')
			count++;
		if (count == 5)
		{
			S.append("0");
			for ( int j = S.length() - 1 ; j > i+1 ; j--)
				S[j] = S[j-1];
			S[i+1] = '0';
			i++;
		}
		i++;
			
	}
	S = "01111110" + S;
	S = S + "01111110";
	cout << "The string after stuffing is ";
	cout << S << endl;

/* Performing destuffing */
	count = 0;
	string DeStuffed;
	//1. Neglect the starting 01111110
	S = S.substr(8);
	for (int i = 0 ; i < S.length() - 8 ; i++)
	{
		if (S[i] == '0')
		{
			DeStuffed += S[i];
			count = 0;
		}
		if ( S[i] == '1')
		{
			DeStuffed += S[i];
			count++;
		}
		if (count == 5)
		{
			i++;
			count = 0;
		}
	}

	cout << "The de-stuffed data is : ";
	cout << DeStuffed << endl;

	return 0;
}
