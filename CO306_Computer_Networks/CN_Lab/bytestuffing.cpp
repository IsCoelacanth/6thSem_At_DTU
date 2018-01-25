#include<iostream>
#include<vector>

using namespace std;


//Funtion to push the delimiter into the output stream.
int stuff_data(vector<int> &a,vector<int> &delim)
{
    for(int i=0;i<delim.size();i++)
        a.push_back(delim[i]);
}

//Pattern Matching function for checking if the sequence contains 
// The delimiter
int check_match(vector<int> &a, vector<int> &delim, int match_index)
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
    vector<int> a,b,delim;
    int i,j,k,n,c=0,m=0,temp,dm=0;


    cout<<"Enter the delimiter size : ";
    cin>>m;
    cout<<"Enter the delimiter sequence : ";
    for(i=0;i<m;i++)
    {
        cin>>temp;
        delim.push_back(temp);
    }
    //Get the sequence
    cout<<"\nEnter the number of bits\n";
    cin>>n;
    cout<<"Enter the bit sequence\n";
	
    stuff_data(a,delim);

    for(i=0;i<n;i++)
    {
        cin>>temp;
        a.push_back(temp);
    }

    for(i=m;i<(n+m);i++)
    {
        if(check_match(a,delim,i))
        {
            stuff_data(a,delim);
        }
        else
        {
            continue;
        }
    }

    stuff_data(a,delim);

    cout<<"Stuffed data\n";
    for(i=0;i<a.size();i++)
    {
        cout<<a[i];
    }
    //---------------------------------------------------//
    dm=0;
    for(int i=m;i<(a.size()-m);i++)
    {
        if(check_match(a,delim,i))
        {
            for(int j=0;j<m;j++)
                b.push_back(a[j]);
            i = i + 2*m - 1;
        }
        else
        {
            b.push_back(a[i]);
        }
    }

    cout<<"\nDe-Stuffed data\n";
    for(i=0;i<b.size();i++)
    {
        cout<<b[i]<<" ";
    }
}
