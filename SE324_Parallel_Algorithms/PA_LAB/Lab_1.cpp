#include<bits/stdc++.h>
using namespace std;

void printvec(vector<int> v)
{
    for(int i = 0 ; i < v.size() ; i++)
        printf("%d ",v[i]);
    printf("\n");
}

void SelectSort(vector<int> &arr)
{
    int len = arr.size();
    int min_in;
    for(int i = 0; i < len ; i++)
    {
        min_in = i;
        for(int j = i+1 ; j < len ; j++)
        {
            if(arr[j] < arr[min_in])
                min_in = j;
        }
        swap(arr[i],arr[min_in]);
    }
}

vector<int> GenerateList(int n)
{
    vector<int> arr;
    for(int i = 0; i < n ; i++)
        arr.push_back(i+1);
    random_shuffle(arr.begin(),arr.end());
    return arr;
}

int main()
{
    int r,n,inc;
    cout<<"Enter the number of elements : ";
    cin>>n;
    cout<<"Enter the increment : ";
    cin>>inc;
    vector<int> arr = GenerateList(n);
    // printvec(arr);
    time_t start,end;
    time(&start);
    SelectSort(arr);
    time(&end);
    double diff = difftime(end,start);
    // printvec(arr);
    cout<<"Sorted in : "<<diff<<"s "<<endl;
    return 0;
}