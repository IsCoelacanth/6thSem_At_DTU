#include<bits/stdc++.h>
using namespace std;


// A map type data structure to hold the follow.
map<char, set<char> > FOLLOW;
// A vector of productions to maintain the order of precedense
vector<string> productions;

// A helper function to print the computed follow
void printFollow()
{
    map<char, set<char> >::iterator it = FOLLOW.begin();

    for (it; it != FOLLOW.end(); it++)
    {
        char ch = it->first;
        cout << ch << " -> { " ;
        set<char>::iterator itt = it->second.begin();
        for (itt; itt != it->second.end(); itt++ )
        {
            cout << *itt << " , ";
        }
        cout << " }" << endl;
    }
}


void Follow(char , char );

// A helper function that checks if the non terminal is in the set
// if it is it skips otherwise it adds it to the set.
void updateFollow(char sym, char v)
{
    if (FOLLOW[sym].find(v) == FOLLOW[sym].end())
        FOLLOW[sym].insert(v);
    else 
        return;
}

// Computed first of the LHS of the non terminal.
void First(char sym, char ch)
{
    if (!isupper(ch))
    {
        updateFollow(sym, ch);
    }

    for(int k = 0 ; k < productions.size(); k++)
    {
        if(productions[k][0] == ch)
        {
            if(productions[k][2] == '$')
                Follow(sym, productions[k][0]);
            else if (islower(productions[k][2]))
                updateFollow(sym, productions[k][2]);
            else
                First(sym, productions[k][2]);
        }
    }
}

// Computes the follow for one non-terminal
void Follow(char sym, char ch)
{
    if (productions[0][0] == ch)
        updateFollow(sym, '$');

    for( int i = 0 ; i < productions.size(); i++)
    {
        int len = productions[i].length();
        for (int j = 2; j < len ; j++)
        {
            if (productions[i][j] == ch)
            {
                if (productions[i][j+1] != '\0')
                    First(sym, productions[i][j+1]);
                if (productions[i][j+1] == '\0' && ch != productions[i][0])
                    Follow(sym, productions[i][0]);
            }
        }
    }
}

// Calls the follow for all Non-terminal symbols
void CommputeFollow(set<char> NT)
{
    set<char>::iterator it = NT.begin();
    for (it; it != NT.end(); it++)
    {
        Follow(*it, *it);
    }
}

int main()
{
    int N;
    cout << "Enter number of productions in grammar : ";
    cin >> N;
    cout << "Enter the productions (Format: S=aAb)" << endl;
    set<char> NT, T;
    for (int i = 0 ; i < N ; i++)
    {
        string tmp;
        cin >> tmp;
        for (int j = 0 ; j < tmp.length(); j++)
        {
            if(isalpha(tmp[j]) && isupper(tmp[j]))
                NT.insert(tmp[j]);
            else
                T.insert(tmp[j]);
        }
        productions.push_back(tmp);
    }
    cout << "Computing follow for grammar : " << endl;
    for(int i = 0 ; i < productions.size(); i++)
        cout << productions[i] << endl;
    CommputeFollow(NT);
    printFollow();
    return 0;
}