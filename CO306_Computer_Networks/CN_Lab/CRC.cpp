#include<iostream>
#include<string>

using namespace std;

string Xor(string a, string b)
{
	string result;
	for (int i = 1; i < b.length() ; i++)
	{
		if (a[i] == b[i])
			result.append("0");
		else
			result.append("1");
	}
	return result;
}

string mod2div( string divident, string divisor)
{
	int pick = divisor.length();
	string tmp;
	string zeros;
	for ( int i = 0; i < pick; i++)
	{
		tmp += divident[i];
		zeros += "0";
	}

	while (pick < divident.length())
	{
		if (tmp[0] == '1')
			tmp = Xor(divisor,tmp) + divident[pick];
		else
			tmp = Xor(zeros, tmp) + divident[pick];
		pick++;
	}

	if (tmp[0] == '1')
		tmp = Xor(divisor,tmp);
	else
		tmp = Xor(zeros,tmp);
	return tmp;
}

void encode( string data, string key)
{
	int key_len = key.length();
	string appended = data;
	for ( int i = 0 ; i < key_len - 1; i++)
	{
		appended.append("0");
	}
	string remainder = mod2div(appended, key);
	string coded = data + remainder;
	cout << "The remainder was : " << remainder << endl;

	cout << "The encoded data is : " << coded << endl;
}

bool check_error(string data, string key)
{
	int key_len = key.length();
	string appended = data;
	for ( int i = 0 ; i < key_len - 1; i++)
	{
		appended.append("0");
	}
	string remainder = mod2div(appended, key);
	for (int i = 0 ; i < remainder.length() ; i++)
		if (remainder[i] == '1')
			return false;
	return true;
}

int main()
{
	string data, key;
	cout << "Enter key : ";
	cin >> key;
	cout << "Enter the data : ";
	cin >> data;
	encode(data,key);
	int flip;
	cout << "Enter a bit to flip (to induce error in seq [0, " << data.length() <<"]) : ";
	cin >> flip;
	if (flip > -1 && flip < data.length())
	{
		if (data[flip] == '1')
			data[flip] = '0';
		else
			data[flip] = '1';
	}
	cout << "Checking for transmission errors on received singal : " << data << endl;
	if (check_error(data,key))
		cout << "Errors in transmission!" << endl;
	else 
		cout << "No Errors found" << endl;
	return 0;
}
	

