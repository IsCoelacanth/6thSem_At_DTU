#include<bits/stdc++.h>
using namespace std;

vector<string> split(string s, string delim)
{
    vector<string> ret;
    string tmp;
    stringstream iss(s);
    while( getline(iss, tmp, delim))
        ret.push_back(tmp);
    return ret;
}

bool in(set<int> m, int k)
{
    if(m.find(k) == m.end())
        return false;
    return true;
}

int main()
{
    int nprods;
    cout << "Enter Number of productions : ";
    cin >> nprods;
    vector<string> prods;
    string temp;
    for (int i = 0 ; i < nprods ;i++)
    {
        cin >> temp;
        prods.push_back(temp);
    }

    map<string, vector<string> > Prds;
    for(int i = 0 ; i < nprods; i++)
    {
        vector<string> lr = split(prods[i], "->");
        vector<string> rhs = split(lr[1], "|");
        set<int> move;
        for (int k = 0 ; k < rhs.size(); k++)
        {
            char ch = rhs[k][0];
            for (j = k+1; j < rhs.size(); j++)
            {
                if (rhs[j][0] == ch)
                    move.insert(j);
                    move.insert(k);
            }
        }
    }
}