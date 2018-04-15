#include <bits/stdc++.h>
using namespace std;

int x = 0;
vector<string> prods;
char arr[] = {"0000000000000000"};

void Follow(char);
void add_to_set(char v)
{
    int t;
    for (t = 0 ; t <= x ; t++)
    {
        if (arr[t] == v)
            return;
    }
    arr[x++] = v;
}

void First(char ch)
{
    if (!isupper(ch))
    {
        add_to_set(ch);
    }

    for(int k = 0 ; k < prods.size(); k++)
    {
        if(prods[k][0] == ch)
        {
            if(prods[k][2] == '$')
                Follow(prods[k][0]);
            else if (islower(prods[k][2]))
                add_to_set(prods[k][2]);
            else
                First(prods[k][2]);
        }
    }
}

void Follow(char ch)
{
    if (prods[0][0] == ch)
        add_to_set('$');
    for( int i = 0 ; i < prods.size(); i++)
    {
        int len = prods[i].length();
        for (int j = 2; j < len ; j++)
        {
            if (prods[i][j] == ch)
            {
                if (prods[i][j+1] != '\0')
                    First(prods[i][j+1]);
                if (prods[i][j+1] == '\0' && ch != prods[i][0])
                    Follow(prods[i][0]);
            }
        }
    }
}

int main()
{
    int len;
    cout << "Enter number of productions : ";
    cin >> len;
    cout << "Enter the productions" << endl;
    set<char> NT;
    for (int i = 0 ; i < len ; i++)
    {
        string tmp;
        cin >> tmp;
        for (int j = 0 ; j < tmp.length(); j++)
        {
            if(isalpha(tmp[j]) && isupper(tmp[j]))
                NT.insert(tmp[j]);
        }
        prods.push_back(tmp);
    }

    set<char>::iterator it = NT.begin();
    for (it; it != NT.end(); it++)
    {
        // cout << arr << endl;
        Follow(*it);
        // cout << arr << endl;
        cout << "Follow of " << *it << " : { ";
        for (int z = 0 ; z < x ; z++)
        {
            cout << arr[z] << ' ';
            arr[z] = 0;
        }
        x = 0;
        cout << '}' << endl;  
    }
    return 0;
}