#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long int i,j,k,l,n,m=9999999999,mini,ma=0;
    string s[100],st,ch,sc="",result,fs,maxi,rs="";
    vector<string>ss;
    vector<string>sp;
    cout << "Enter number of productions : ";
    cin>>n;
    cout << "Enter the production : " << endl;
    for(i=1;i<=n;i++)
    {
        cin>>s[i];
    }
    for(i=1;i<=n;i++)
    {
        st=s[i];
        sc="";

        for(j=0;j<st.length();j++)
        {
            if(i==1)
            {
                fs=st[0];
            }
            if(st[j]=='=')
            {
               l=j;
            }
        }

        if(i==1)
        {

        for(k=l+1;k<st.length();k++)
        {
            if(st[k]=='|')
            {
                ss.push_back(sc);
                sc="";
            }
            if(st[k]!='|')
            {
                ch=st[k];
                sc=sc+ch;
            }

        }
        ss.push_back(sc);
        }
        //cout<<sc<<endl;


    }

    for(k=0;k<ss.size();k++)
    {
        mini=ss[k].size();
        m=min(m,mini);
        maxi=ss[k];
        //cout<<ss[k]<<endl;

    }
    //cout<<maxi<<endl;




    for(k=0;k<m;k++)
    {
        //cout<<ss[0][k]<<endl;
    }

    for (int i=0; i<m; i++)
    {

        char current = ss[0][i];

        for (int j=1 ; j<ss.size(); j++)
        {
            if (ss[j][i] != current)
            {
                   break;
            }
             result.push_back(current);
        }

    }

    for(j=0;j<ss.size();j++)
    {
        maxi=ss[j];
        //cout<<maxi<<result.length()<<endl;
    for(k=0;k<maxi.length();k++)
    {


        if(k>=result.length())
        {
            rs=rs+maxi[k];


        }

        //cout<<rs<<endl;

    }
            if(j!=ss.size()-1)
            {
                  rs=rs+'|';
            }
    }

    cout<<fs<<"="<<result<<fs<<"'"<<endl;
    cout<<fs<<"'"<<"="<<rs<<endl;

    for(i=2;i<=n;i++)
    {
        cout<<s[i]<<endl;
    }



    return 0;


}