#include<bits/stdc++.h>
using namespace std;

map<char, map<char, int> > M = {
    {'E', {{'a', 0}, {'(', 0}}},
    {'D', {{'+', 1}, {')', 2}, {'$', 2}}},
    {'T', {{'a', 3}, {'(', 3}}},
    {'S', {{'*', 4}, {'+', 5}, {')', 5}, {'$', 5}}},
    {'F', {{'(', 6}, {'a', 7}}},
};

map<int, string> Grammar = {
    {0, "E=TD"},
    {1, "D=+TD"},
    {2, "D=$"},
    {3, "T=FS"},
    {4, "S=*FS"},
    {5, "S=$"},
    {6, "F=(E)"},
    {7, "F=a"}
};

void printStack(vector<char> s)
{
    cout<<endl;
    for (int i = 0 ; i < s.size() ; i ++ )
        cout << s[i] << ' ';
}

void Parse(string s)
{
    vector<char> stk;
    stk.push_back('#');
    stk.push_back('E');
    char peak = stk.back();
    int i = 0;
    printStack(stk);
    while(stk.size() > 0)
    {
        if (stk.size() <=3)
            cout << "\t\t\tinputs : " << s.substr(i) ;
        else
            cout << "\t\tinputs : " << s.substr(i) ;
        if (peak == s[i])
        {
            if (stk.size() <=3)
                cout << "\t\t\t\tMatched ID";
            else
                cout << "\t\t\tMatched ID";
            stk.pop_back();
            i++;
        }
        else if (islower(peak))
        {
            cout << "Error in parsing, expected : " << peak <<" got : "<<s[i]<<endl;
            return;
        }
        else if (M[peak].find(s[i]) == M[peak].end())
        {

            cout << "Error in parsing, invalid expression " << M[peak][s[i]] << endl;
            return;
        }
        else
        {
            char pp = peak;
            stk.pop_back();
            string prod = Grammar[M[pp][s[i]]];
            int z = prod.length() - 1;
            if (stk.size() <=3)
                cout << "\t\t\tAction : " << prod;
            else
                cout << "\t\tAction : " << prod;
            while(prod[z] != '=' && prod[z] != '$')
            {
                stk.push_back(prod[z]);
                z--;
            }
            // cout << endl;
        }
        peak = stk.back();
        printStack(stk);
        if (peak == '#' && s[i] == '$')
        {
            cout << "Parsed successfully" << endl;
            return ;
        }
    }

}
int main()
{
    cout << "Enter some expression : ";
    string expr;
    cin >> expr;
    if (expr.back() != '$')
        expr += "$";
    Parse(expr);
}