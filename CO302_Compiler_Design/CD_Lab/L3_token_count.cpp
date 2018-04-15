#include<bits/stdc++.h>
using namespace std;

map<string, pair<string, int> > Table;
string t[] = { "auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while"
};
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
		// cout << "Line : " << line << endl;
		if (line[0] == '#' || (line[0] == '/' && line[1] == '/'))
			continue;
		int i = 0;
		while( i < line.length())
		{
			temp.clear();
			if (line[i] == ' ' || line[i] == '\t')
			{
				while(line[i] == ' ' || line[i] == '\t')
					i++;
				// getchar();
				// i--;
			}
			else if (isalpha(line[i]))
			{
				while ((line[i] != ' ' ) && i < line.length() && isalnum(line[i]))
					temp += line[i++];
				// cout << "temp : " << temp << endl;
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
				// i--;
			}
			else if (isdigit(line[i]))
			{
				while(isdigit(line[i]))
					temp += line[i++];
				// cout << "temp : " << temp << endl;
				Table[temp].second++;
				Table[temp].first = "Constant/Literal";
				temp.clear();
			}
			else
			{
				while (line[i] != ' ' && i < line.length() && !(isalnum(line[i])))
					temp += line[i++];
				// cout << "temp : " << temp << endl;
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