#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
using namespace std;

char GetClass(string S)
{
    int i = 0;
    while(S[i] != '.')
        i++;
    i--;
    
    int ip = 0;
    int j = 1;
    while (i >= 0)
    {
        ip += (S[i] - '0') * j;
        j *= 10;
        i--;
    }
    // Class A
    if (ip >=1 && ip <= 126)
        return 'A';
 
    // Class B
    else if (ip >= 128 && ip <= 191)
        return 'B';
 
    // Class C
    else if (ip >= 192 && ip <= 223)
        return 'C';
 
    // Class D
    else if (ip >= 224 && ip <= 239)
        return 'D';
 
    // Class E
    else
        return 'E';
    
}

void GetIDs(string S, char IpClass)
{
    string NetID, HostID;

    if (IpClass == 'A')
    {
        int j = 0;
        while(S[j] != '.')
            NetID += S[j++];
        j++;
        while (j < S.length())
            HostID += S[j++];

        cout << "Network ID in " << S << " is " << NetID << endl;
        cout << "Host ID in " << S << " is " << HostID << endl;
    }

    else if (IpClass == 'B')
    {
        int j = 0, dc = 0;
        while( dc < 2)
        {
            NetID += S[j++];
            if (S[j] == '.')
                dc++;
        }
        j++;

        while( j < S.length())
            HostID += S[j];
        cout << "Network ID in "<< S << " is " << NetID << endl;
        cout << "Host ID in "<< S << " is " << HostID << endl;
    }

    else if (IpClass == 'C')
    {
        int j = 0, dc = 0;
        while( dc < 3)
        {
            NetID += S[j++];
            if (S[j] == '.')
                dc++;
        }
        j++;

        while( j < S.length())
            HostID += S[j];
        cout << "Network ID in "<< S << " is " << NetID << endl;
        cout << "Host ID in "<< S << " is " << HostID << endl;
    }

    else
    {
        cout << "IP : " << S << " is of Class D/E " << endl;
        cout << "Classes D and E don't have Network and Host IDs " << endl;
}
    }
        

int main()
{
    int t;
    string S;
    char Class;
    
    cout << "Enter how many IPv4 addresses to test : ";
    cin >> t;
    while (t--)
    {
        for(int i = 0 ; i < 4 ; i ++)
        {
            ostringstream st;
            st << rand()%256;
            S += st.str();
            if( i < 3)
                S += '.';
        }

        Class = GetClass(S);
        cout << "IPv4 Class : " << Class << endl;
        GetIDs(S, Class);
        S.clear();
    }
}