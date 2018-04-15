/*
	recursive descent parser for the grammar:
	E -> TE'
	E' -> +TE' | @
	T -> FT'
	T' -> *FT' | @
	F -> id | (E)
	@ is epsilon
*/

#include <iostream>
#include <string>
#include <cctype>
#include <stdlib.h>
using namespace std;

int l;
string buffer;
void E();
void E1();
void T();
void T1();
void F();
void ADV(char);

void E()
{
	cout << "Called T from E" << endl;
	T();
	cout << "Called E1 from E" << endl;
	E1();
}

void T()
{
	cout << "Called F from T" << endl;
	F();
	cout << "Called T1 from T" << endl;
	T1();
}

void F()
{
	if (isdigit(buffer[l]))
	{
		cout << "Matched ID" << endl;
		ADV(buffer[l]);
	}
	else if (buffer[l] == '(')
	{
		cout << "Matched (" << endl;
		ADV('(');
		cout << "Called E from F" << endl;
		E();
		cout << "Matched )" << endl;
		if (buffer[l] == ')')
		{
			cout << "Matched )" << endl;
			ADV(')');
		}
		else
		{
			cout << "expected ) got" << buffer[l] << " exiting" << endl;
			exit(0);
		}
	}
	else
	{
		cout << "expected 'id' got " << buffer[l] << " exiting" << endl;
		exit(0);
	}
}

void E1()
{
	if (buffer[l] == '+')
	{
		cout << "Matched +" << endl;
		ADV('+');
		cout << "Called T from E1" << endl;
		T();
		cout << "Called E1 from E1" << endl;
		E1();
	}
	else
		return;
}

void T1()
{
	if (buffer[l] == '*')
	{
		cout << "Matched *" << endl;
		ADV('*');
		cout << "Called F from T1" << endl;
		F();
		cout << "Called T1 from T1" << endl;
		T1();
	}
	else
		return;
}

void ADV(char ch)
{
	if (buffer[l] == ch)
		l++;
	else
	{
		cout << "Error in parsing" << endl;
		exit(0);
	}
}
int main()
{
	cout << "Enter the string to parse terminated with $ : ";
	cin >> buffer;
	l = 0;
	cout << "Called E from main" << endl;
	E();
	cout << buffer[l] << endl;
	if (buffer[l] == '$')
	{
		cout << "Successfully parsed" << endl;
	}
	else
	{
		cout << "Error in parsing " << endl;
	}
}