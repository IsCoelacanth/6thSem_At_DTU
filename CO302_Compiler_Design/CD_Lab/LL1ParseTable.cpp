#include<bits/stdc++.h>
using namespace std;

map<char, set<char> > FOLLOW;
map<char, set<char> > FIRST;

map<char, map<char, int> > M;
vector<string> productions;

// 1. Computer First 
void add_to_First(char sym, char v)
{
    if (FIRST[sym].find(v) == FIRST[sym].end())
    {
        FIRST[sym].insert(v);
    }
    else 
        return;
}

void First(char sym, char ch)
{
    char temp[25];
    if (!isupper(ch))
    {
        add_to_First(sym, ch);
        return;
    }
    for (int cnt = 0 ; cnt < productions.size(); cnt ++) 
    {
        if (productions[cnt][0] == ch)
        {
            if(productions[cnt][2] == '$')
            {
                add_to_First(sym, '$');
            }

            else
            {
                int j = 2;
                while(productions[cnt][j] != '\0')
                {
                    int x = 0;
                    First(productions[cnt][j], productions[cnt][j]);
                    set<char>::iterator it = FIRST[productions[cnt][j]].begin();
                    for (it ; it != FIRST[productions[cnt][j]].end() ; it++)
                    {
                        add_to_First(sym, *it);
                    }
                    for (int k = 0 ; temp[k] != '\0' ; k++)
                    {
                        if (temp[k] == '$')
                        {
                            x = 1;
                            break;
                        }
                    }
                    if(!x)
                        break;
                    j++;
                }
            }
        }
    }
    return;
}

// 2. Computer Follow
void Follow(char , char );
void add_to_follow(char sym, char v)
{
    if (FOLLOW[sym].find(v) == FOLLOW[sym].end())
        FOLLOW[sym].insert(v);
    else 
        return;
}

void First_for_Follow(char sym, char ch)
{
    if (!isupper(ch))
    {
        add_to_follow(sym, ch);
    }

    for(int k = 0 ; k < productions.size(); k++)
    {
        if(productions[k][0] == ch)
        {
            if(productions[k][2] == '$')
                Follow(sym, productions[k][0]);
            else if (islower(productions[k][2]))
                add_to_follow(sym, productions[k][2]);
            else
                First_for_Follow(sym, productions[k][2]);
        }
    }
}

void Follow(char sym, char ch)
{
    if (productions[0][0] == ch)
        add_to_follow(sym, '$');
    for( int i = 0 ; i < productions.size(); i++)
    {
        int len = productions[i].length();
        for (int j = 2; j < len ; j++)
        {
            if (productions[i][j] == ch)
            {
                if (productions[i][j+1] != '\0')
                    First_for_Follow(sym, productions[i][j+1]);
                if (productions[i][j+1] == '\0' && ch != productions[i][0])
                    Follow(sym, productions[i][0]);
            }
        }
    }
}

// 3. Build table:
void Build_Table()
{
    for (int i = 0 ; i < productions.size(); i++)
    {
        string RHS = productions[i].substr(2);
        set<char> fst = FIRST[RHS[0]];
        set<char>::iterator it = fst.begin();
        for(it; it != fst.end(); it++)
        {
            // cout<<*it;
            if(*it == '$')
            {
                // cout << "Found a epsilon"<<endl;
                set<char> foll = FOLLOW[productions[i][0]];
                // cout << foll.size() << " The follow is yuge " << endl;
                set<char>::iterator itt = foll.begin();
                for (itt; itt != foll.end(); itt++)
                {
                    if (*itt == '$')
                    {
                        M[productions[i][0]]['$'] =  i;
                        // cout << "Table : " << i <<' '<<0<<'s'<<'='<<i+1 <<'_'<<M[productions[i][0]]['$']<<endl;
                    }
                    else
                        M[productions[i][0]][*itt] = i;
                        // cout << "Table : " << i <<' '<<0<<'s'<<'='<<i+1 <<'_'<<M[productions[i][0]][*itt]<<endl;
                }

            }
            else
            {
                M[productions[i][0]][*it] = i;
            }
        }
    }
}

void printTable(set<char> NT, set<char> T)
{
    T.insert('$');
    set<char>::iterator Ts = T.begin();
    cout <<"NT" << '\t'<< ' ' << '\t';
    for (Ts ; Ts != T.end(); Ts++)
        cout << *Ts << '\t';
    cout << endl;
    set<char>::iterator NTs = NT.begin();
    for (NTs ; NTs != NT.end() ; NTs++)
    {
        cout << *NTs << '\t' << ':' << '\t';
        map<char, int> tmap = M[*NTs];

        // map<char, int>::iterator mit = M[*NTs].begin();
        // for ( mit ; mit != M[*NTs].end() ; mit++)
        //     cout << mit->first << "->" << mit->second << endl;

        set<char>::iterator Ts = T.begin();
        for (Ts; Ts != T.end(); Ts++)
        {
            if(M[*NTs].find(*Ts) != M[*NTs].end())
            {
                cout << productions[M[*NTs][*Ts]] << '\t';
            }
            else 
                cout << "err" << '\t';
        }
        cout << endl;
    }
}

void CommputeFollow(set<char> NT)
{
    set<char>::iterator it = NT.begin();
    for (it; it != NT.end(); it++)
    {
        Follow(*it, *it);
    }
}

void CommputeFirst(set<char> NT, set<char> T)
{
    set<char>::iterator it = NT.begin();
    for (it; it != NT.end(); it++)
    {
        First(*it, *it); 
    }
    it = T.begin();
    for (it; it != T.end(); it++)
    {
        First(*it, *it);  
    }
}

int main()
{
    int len;
    cout << "Enter number of productions : ";
    cin >> len;
    cout << "Enter the productions" << endl;
    set<char> NT, T;
    for (int i = 0 ; i < len ; i++)
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

    cout << "1. Compute First : " << endl << "Done" << endl;
    cout << "2. Compute Follow : " << endl << "Done" << endl;
    cout << "3. Compute First : " << endl << "Done" << endl;
    CommputeFirst(NT, T);
    CommputeFollow(NT);
    Build_Table();
    printTable(NT, T);
    return 0;
}