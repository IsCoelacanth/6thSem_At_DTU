#include<bits/stdc++.h>
using namespace std;

map<string, pair<string, string> > Table;
string t[] = { "auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while"
};
set<string> keyw(t, t+13);
string o[] = { "+", "-", "*", "*", "<<", ">>", ".", "==", "<", ">", "!=", "!", "=" }; 
set<string> opr(o, o + 13);
int main()
{
	ifstream fin("Text.cpp");
	string line, temp, lastID;
    bool assign;
    int k = 0;
	while (!fin.eof())
	{
        cout << "line : "<<k++<<endl;
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
					Table[temp].second = "N/A";
					Table[temp].first = "KW";
				}
				else if (!(Table.find(temp) != Table.end()))
				{
					Table[temp].second = "N/A";;
					Table[temp].first = "ID";
                    lastID = temp;
				}
                else
                {
                    lastID = temp;
                }
				temp.clear();
				// i--;
			}
			else if (isdigit(line[i]))
			{
				while(isdigit(line[i]))
					temp += line[i++];
				// cout << "temp : " << temp<< " " << lastID<< endl;
				Table[temp].second = "N/A";;
				Table[temp].first = "CN";
                if(assign == true && lastID.length() > 0)
                {
                    // cout << "Assigning "<<endl;
                    Table[lastID].second = temp;
                    assign = false;
                    lastID.clear();
                }
				temp.clear();
			}
			else
			{
				while (line[i] != ' ' && i < line.length() && !(isalnum(line[i])))
					temp += line[i++];
				// cout << "temp : " << temp << endl;
				if (opr.find(temp) != opr.end())
				{
					Table[temp].second = "N/A";;
					Table[temp].first = "OP";
				}
                if (temp == "=" )
                {
				    assign = true;
                    // cout << "assign = true"<<endl;
                }
			}
            // cout << "Last ID = " << lastID << endl;
				
		}
        map<string, pair<string, string> >::iterator it;
        for (it = Table.begin(); it != Table.end(); it++)
        {
            cout << "<name : " << it->first << " ,type : " << it->second.first << " , Attr : " << it->second.second << ">" << endl;
        }
        assign = false;
        lastID.clear();
        Table.clear();
	}
	fin.close();
	return 0;
}