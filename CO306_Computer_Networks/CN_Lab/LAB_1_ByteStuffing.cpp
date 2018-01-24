#include<iostream>
#include<string>

using namespace std;

int main()
{
	string in, out;
	cout << "enter the character sequence " << endl << ">>> ";
	cin >> in;
	out += "DLESTX ";
	int len = in.length();

	for (int i = 0; i < len; i++)
	{
		if (in[i] == 'd' && in[i + 1] == 'l' && in[i + 2] == 'e')
			out += " dle ";
		out += in[i];
	}

	out += " DLEETX";
	cout << "After stuffing : " << out << endl;
}