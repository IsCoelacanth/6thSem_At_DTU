#include<bits/stdc++.h>
using namespace std;


vector<string> prods;
void add_to_set(char *arr, char v)
{
    int t;
    for (t = 0 ; arr[t] != '\0'; t++)
    {
        if (arr[t] == v)
            return;
    }
    arr[t] = v;
    arr[t+1] = '\0';
}

void First(char *arr, char ch)
{
    char temp[25];
    arr[0] = '\0';
    if (!isupper(ch))
    {
        add_to_set(arr, ch);
        return;
    }
    for (int cnt = 0 ; cnt < prods.size(); cnt ++) 
    {
        if (prods[cnt][0] == ch)
        {
            if(prods[cnt][2] == '$')
                add_to_set(arr, '$');
            else
            {
                int j = 2;
                while(prods[cnt][j] != '\0')
                {
                    int x = 0;
                    First(temp, prods[cnt][j]);
                    for (int k = 0 ; temp[k] != '\0' ; k++)
                        add_to_set(arr, temp[k]);
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


int main()
{
    char arr[25];
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
            if (isalpha(tmp[j]) && islower(tmp[j]))
                T.insert(tmp[j]);
            else if(isalpha(tmp[j]) && isupper(tmp[j]))
                NT.insert(tmp[j]);
        }
        prods.push_back(tmp);
    }

    set<char>::iterator it = NT.begin();
    for (it; it != NT.end(); it++)
    {
        First(arr, *it);
        cout << "First of " << *it << " : {";
        for (int z = 0 ; arr[z] != '\0' ; z++)
            cout << arr[z] << ',';
        cout << '}' << endl;  
    }
    set<char>::iterator it = T.begin();
    for (it; it != NT.end(); it++)
    {
        First(arr, *it);
        cout << "First of " << *it << " : { ";
        for (int z = 0 ; arr[z] != '\0' ; z++)
            cout << arr[z] << ' ';
        cout << '}' << endl;  
    }
    return;
    

}