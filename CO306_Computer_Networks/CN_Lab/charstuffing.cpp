#include<iostream>
#include<vector>

using namespace std;

int stuff_data(vector<char> &a,vector<char> &delim)
{
    for(int i=0;i<delim.size();i++)
        a.push_back(delim[i]);
}

int check_match(vector<char> &a, vector<char> &delim, int match_index)
{
    for(int i=match_index,j=0; i<a.size() && j<delim.size();i++,j++)
    {
        if(a[i] == delim[j])
            continue;
        else
            return 0;
    }

    return 1;
}

int main()
{
    vector<char> a,b,delim;
    int i,n,m;
    char temp;

    cout<<"Enter the delimiter size\n";
    cin>>m;
    cout<<"Enter the delimiter sequence\n";
    for(i=0;i<m;i++)
    {
        cin>>temp;
        delim.push_back(temp);
    }

    //--------------------------------------------------------//
    cout<<"\nEnter the number of characters\n";
    cin>>n;
    cout<<"Enter the character sequence\n";

    stuff_data(b,delim);

    for(i=0;i<n;i++)
    {
        cin>>temp;
        a.push_back(temp);
    }

    for(i=0;i<n;i++)
    {
        if((((a.size()-1) - i) > delim.size()) && check_match(a,delim,i))
        {
                stuff_data(b,delim);
                stuff_data(b,delim);
                i = i + m - 1;
        }
        else
        {
            b.push_back(a[i]);
        }
    }

    stuff_data(b,delim);

    cout<<"Stuffed data\n";
    for(i=0;i<b.size();i++)
    {
        cout<<b[i];
    }
    //---------------------------------------------------//
    a.clear();
    for(int i=m;i<(b.size()-m);i++)
    {
        if(check_match(b,delim,i))
        {
            stuff_data(a,delim);
            i = i + 2*m - 1;
        }
        else
        {
            a.push_back(b[i]);
        }
    }

    cout<<"\nDe-Stuffed data\n";
    for(i=0;i<a.size();i++)
    {
        cout<<a[i]<<" ";
    }
}
