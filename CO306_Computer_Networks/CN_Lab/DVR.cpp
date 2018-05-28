#include<bits/stdc++.h>
using namespace std;
                                                
struct node
{
    unsigned dist[6];
    unsigned from[6];
}
DVR[10];
int main()
{
    int costmat[6][6];
    int nodes, i, j, k;
    cout<<"\n\n Enter the number of nodes in the network : ";
    cin>>nodes; //Enter the nodes
    cout<<"\n Enter the cost matrix showing cost between each nodes : \n" ;
    for(i = 0; i < nodes; i++)
     {
        for(j = 0; j < nodes; j++)
        {
            cin>>costmat[i][j];
            costmat[i][i] = 0;
            DVR[i].dist[j] = costmat[i][j]; //initialise the distance equal to cost matrix
            DVR[i].from[j] = j;
        }
    }
            for(i = 0; i < nodes; i++) 
            for(k = 0; k < nodes; k++)
                if(DVR[i].dist[j] > costmat[i][k] + DVR[k].dist[j])
                {   //We calculate the minimum distance
                    DVR[i].dist[j] = DVR[i].dist[k] + DVR[k].dist[j];
                    DVR[j].dist[i] = DVR[i].dist[j];
                    DVR[i].from[j] = k;
                    DVR[j].from[i] = k;
                                                                
                }
        for(i = 0; i < nodes; i++)
        {
            cout<<"\n\n For router: "<<i+1;
            for(j = 0; j < nodes; j++)
                cout<<"\t\n node "<<j+1<<" via "<<DVR[i].from[j]+1<<" Distance "<<DVR[i].dist[j];
        }
    cout<<" \n\n ";
    return 0;
}
