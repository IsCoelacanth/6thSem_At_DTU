#include<iostream>
#include<vector>
#include<queue>

using namespace std;

vector<int> input;
int n,m;
int temp;
vector<int> poly;
queue<int> remainder;

void printq(queue<int> q)
{
    while(!q.empty())
    {
        cout<<q.front()<<" ";
        q.pop();
    }
    cout<<endl;
}

void clearq(queue<int> &q)
{
    while(q.size())
        q.pop();
}

queue<int> get_remainder()
{
    int index = 0;
    queue<int> remainder,div;
    //move to first 1
    while(input[index] != 1 && index < m)
        index++;

    //initialize div
    for(int i = 0; i < n ; i++)
    {
        div.push(input[index]);
        index++;
    }

    //perform division
    while(index < m)
    {
        clearq(remainder);

        for(int i=0;i<n;i++)
        {
            remainder.push(div.front() ^ poly[i]);
            div.pop();
        }

        //move to first 1 and fill div
        div = remainder;
        while(!div.empty() && div.front() == 0)
            div.pop();
        while(div.size() < n && index < m)
        {
            div.push(input[index]);
            index++;
            if(div.front() == 0)
                div.pop();
        }
    }

    //handles last division
    if(div.size() == n)
    {
        clearq(remainder);
        for(int i=0;i<n;i++)
        {
            remainder.push(div.front() ^ poly[i]);
            div.pop();
        }
    }

    remainder.pop();
    return remainder;

}

int main()
{
    cout<<"Enter degree of polynomial\n";
    cin>>n;
    cout<<"Enter polynomial bits\n";
    for(int i=0;i<n;i++)
    {
        cin>>temp;
        poly.push_back(temp);
    }

    cout<<"Enter input length\n";
    cin>>m;
    cout<<"Enter input bit sequence\n";
    for(int i=0;i<m;i++)
    {
        cin>>temp;
        input.push_back(temp);
    }
    m=m+n-1;

    //push n-1 zeros
    for(int i=1;i<n;i++)
        input.push_back(0);

    //----------------------------------//
    remainder = get_remainder();

    printq(remainder);

    int j=remainder.size();
    while(!remainder.empty())
    {
        input[m-j] = remainder.front();
        remainder.pop();
        j--;
    }

    cout<<"Modified Sequence\n";
    for(int i=0;i<m;i++)
    {
        cout<<input[i]<<" ";
    }
    cout<<endl;
    //----------------------------------//

    int bitno;
    cout<<"Enter bit number to flip (Enter -1 to make no change)\n";
    cin>>bitno;
    if(bitno > -1)
        input[bitno] = 1 - input[bitno];
    //----------------------------------//


    cout<<"Answer\n";

    remainder = get_remainder();

    while(!remainder.empty())
    {
        if(remainder.front())
        {
            cout<<"Error detected!\n";
            break;
        }
        remainder.pop();
        if(remainder.size()==0)
            cout<<"No error!\n";
    }


    return 0;
}
