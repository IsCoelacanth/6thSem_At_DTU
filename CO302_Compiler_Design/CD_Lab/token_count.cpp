#include<bits/stdc++.h>
using namespace std;

map<string, pair<string, int> > Table;
string t[] = { "int", "float", "char", "void", "cout", "cin", "while", "for", "using", "namespace", "if", "return", "else" };
set<string> keyw(t, t+13);
string o[] = { "+", "-", "*", "*", "<<", ">>", ".", "==", "<", ">", "!=", "!", "=" };
set<string> opr(o, o + 13);
int main()
{
	ifstream fin("Text.cpp");
	string line, temp;
	while (!fin.eof())
	{
		getline(fin, line);
		//cout << "Line : " << line << endl;
		if (line[0] == '#' || (line[0] == '/' && line[1] == '/'))
			continue;
		for (int i = 0; i < line.length(); i++)
		{
			temp.clear();
			if (line[i] == ' ')
			{
				i++; continue;
			}
			if (isalpha(line[i]))
			{
				while ((line[i] != ' ' ) && i < line.length() && isalnum(line[i]))
					temp += line[i++];
				//cout << "temp : " << temp << endl;
				if (keyw.find(temp) != keyw.end())
				{
					Table[temp].second++;
					Table[temp].first = "Keyword";
				}
				else
				{
					Table[temp].second++;
					Table[temp].first = "Identifier";
				}
				temp.clear();
			}
			else
			{
				while (line[i] != ' ' && i < line.length() && !(isalnum(line[i])))
					temp += line[i++];
				cout << "temp : " << temp << endl;
				if (opr.find(temp) != opr.end())
				{
					Table[temp].second++;
					Table[temp].first = "Operator";
				}
				temp.clear();
			}
				
		}
	}
	fin.close();

	map<string, pair<string, int> >::iterator it;
	for (it = Table.begin(); it != Table.end(); it++)
	{
		cout << "Name : " << it->first << "      Type : " << it->second.first << " Count : " << it->second.second << endl;
	}
	return 0;
}