#include<iostream>
#include<set>
#include<map>
#include<vector>
using namespace std;

map<set<int> , int> mapper_to_int;
map<int , set<int> > mapper_to_set;
vector<vector<int> > dfa_table;
int temp;
set<int> moves;
vector<int> mov_vec;
int symbols;
int states_nfa;
int dfa_states;

int main()
{
    cout<<"Enter number of symbols\n";
    cin>>symbols;
    cout<<"Enter number of states\n";
    cin>>states_nfa;

    //initialize table and add null state
    for(int i=0;i<symbols;i++)
        mov_vec.push_back(0);
    dfa_table.push_back(mov_vec);
    dfa_states = states_nfa + 1;

    //add old states
    for(int i = 1; i <= states_nfa; i++)
    {
        moves.insert(i);
        mapper_to_int[moves] = i;
        mapper_to_set[i] = moves;
        moves.clear();
    }

    //input
    cout<<"Enter the transition table\n";
    for(int i=1;i<=states_nfa;i++)
    {
        cout<<"State : "<<i<<endl;
        moves.clear();
        mov_vec.clear();
        for(int j=0;j<symbols;j++)
        {
            temp = -2;
            moves.clear();
            cout<<"Input symbol : "<<j<<" (Enter -1 to end input)\n";
            while(temp != -1)
            {
                cin>>temp;
                if(temp!=-1)
                    moves.insert(temp);
            }

            if(moves.empty())
            {
                mov_vec.push_back(0);
                continue;
            }
            //if set is new, add to list
            if(mapper_to_int[moves] == 0)
            {
                mapper_to_int[moves] = dfa_states;
                mapper_to_set[dfa_states] = moves;
                mov_vec.push_back(dfa_states);
                dfa_states++;
            }
            else
            {
                mov_vec.push_back(mapper_to_int[moves]);
            }
        }
        dfa_table.push_back(mov_vec);
    }
    //----------------------------------------//

    int new_states = dfa_states;
    int curr_state = states_nfa+1;
    set<int> curr;
    moves.clear();
    mov_vec.clear();

    //while all states not visited
    while(curr_state < new_states)
    {
        mov_vec.clear();
        moves.clear();
        curr = mapper_to_set[curr_state];

        for(int i=0;i<symbols;i++)
        {

            moves.clear();
            for(auto f : curr)   //iterate current state set
            {
                if(dfa_table[f][i]!=0)
                {
                    for(auto g : mapper_to_set[dfa_table[f][i]])
                        if(g != 0)
                            moves.insert(g);
                }
            }

            //if set is new, add to list
            if(moves.empty())
            {
                mov_vec.push_back(0);
                continue;
            }
            if(mapper_to_int[moves] == 0)
            {
                mapper_to_int[moves] = new_states;
                mapper_to_set[new_states] = moves;
                mov_vec.push_back(new_states);
                new_states++;
            }
            else
            {
                mov_vec.push_back(mapper_to_int[moves]);
            }

        }
        dfa_table.push_back(mov_vec);
        curr_state++;
    }

    //----------------------------------------//
    //print dfa
    for(int i=1 ; i<new_states ;i++)
    {
        cout<<i<<" : ";
        for(int j=0; j<symbols; j++)
        {
            cout<<dfa_table[i][j]<<" ";
        }
        cout<<endl;
    }

    return 0;
}
