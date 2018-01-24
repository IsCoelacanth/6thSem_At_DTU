#include<iostream>
#include<vector>

using namespace std;

int stuff_data(vector<int> &a)
{
    a.push_back(0);
    a.push_back(1);
    a.push_back(1);
    a.push_back(1);
    a.push_back(1);
    a.push_back(1);
    a.push_back(1);
    a.push_back(0);
}

int main()
{
    vector<int> a,b;
    int i,j,k,n,c=0,pos=0,temp;
    cout<<"\n Enter the number of bits\n";
    cin>>n;
    cout<<"Enter the bit sequence\n";

    stuff_data(a);

    for(i=0;i<n;i++)
    {
        cin>>temp;
        a.push_back(temp);
        if(temp == 1)
        {
            c++;
        }
        else
        {
            c=0;
        }
        if(c==5)
        {
            a.push_back(0);
            c=0;
        }

    }

    stuff_data(a);

    cout<<"Stuffed data\n";
    for(i=0;i<a.size();i++)
    {
        cout<<a[i];
    }

    c=0;
    for(int i=8;i<(a.size()-8);i++)
    {
        if(a[i] == 1)
        {
            b.push_back(1);
            c++;
        }
        else
        {
            b.push_back(0);
            c=0;
        }
        if(c==5)
        {
            i++;
            c=0;
        }
    }

    cout<<"\nDe-Stuffed data\n";
    for(i=0;i<b.size();i++)
    {
        cout<<b[i]<<" ";
    }
}
