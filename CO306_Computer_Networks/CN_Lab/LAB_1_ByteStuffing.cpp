/*
To implement byte/character stuffing and destuffing
 This implementation is unrestricted in terms of the size
 of input sequence.
 */

#include<iostream>
#include<string>

using namespace std;

int main()
{
	string in, out;
	cout << "enter the character sequence " << endl << ">>> ";
	cin >> in;
	out += "DLESTX";
	int len = in.length();

	for (int i = 0; i < len; i++)
	{
		if (in[i] == 'd' && in[i + 1] == 'l' && in[i + 2] == 'e')
			out += "dle";
		out += in[i];
	}

	out += "DLEETX";
	cout << "After stuffing : " << out << endl;

	in.clear();
	for(int i = 6; i < out.length()-6;i++)
	{
		if (out[i] == 'd' && out[i + 1] == 'l' && out[i + 2] == 'e')
		{
			i+=5;
			in += "dle";
		}
		else 
			in += out[i];
	}
	cout << "The de-stuffed data is : ";
	cout << in << endl;
	return 0;
}