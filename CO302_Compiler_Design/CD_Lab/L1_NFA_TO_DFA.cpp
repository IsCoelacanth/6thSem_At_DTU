#include<bits/stdc++.h>
using namespace std;

#define MX_NF 10
#define MX_AL 10

//1. Data structure to define an NFA state
//2. A matrix of all Transitions initialized 
//   to -1 i.e blank

class NFA_state
{
public:
	int transitions[MX_AL][MX_NF];

	NFA_state()
	{
		for (int i = 0; i < MX_AL; i++)
		{
			for (int j = 0; j < MX_NF; j++)
			{
				transitions[i][j] = -1;
			}
		}
	}
} *NFA_states;
//Initialize a pointer to hold array of NFA states

// Data structure to represent a DFA state
// 1. A flag to show final state
// 2. A bitset to show the NFA states that make it up
// 3. A bitset of transitions
// 4. An array of symbolic transitions
struct DFA_State
{
	bool is_final;
	bitset<MX_NF> Const_NFA_states;
	bitset<MX_NF> transitions[MX_AL];
	int symbTrans[MX_AL];
};

//Defining Global Variables
//1.	The final states in the NFA
//2.	The final states in the DFA
//3.	The states in the DFA
//4.	A queue of DFA states that are to be completed

set<int> NFA_Final;
vector<int> DFA_Final;
vector<DFA_State*> DF_states;
queue<int> to_do_DFA;

//1. N -> The number of states
//2. M -> The input alphabet size
int N, M;

//Function 1. Find the Epsilon Closure of a state and store it.

void E_Close(int state, bitset <MX_NF> &closure)
{
	for (int i = 0; i < N && NFA_states[state].transitions[0][i] != -1; i++)
	{
		if (closure[NFA_states[state].transitions[0][i]] == 0)
		{
			closure[NFA_states[state].transitions[0][i]] = 1;
			E_Close(NFA_states[state].transitions[0][i], closure);
		}
	}
}

// Function 2. Find the Epsilon Closure of the set of NFA states

void E_Close(bitset<MX_NF> state, bitset<MX_NF> &closure)
{
	for (int i = 0; i < N; i++)
	{
		if (state[i] == 1)
		{
			E_Close(i, closure);
		}
	}
}

// Function 3. Build the bitset showing the states an NFA state k 
// can reach after making a transition from X on the input Y

void MoveNFA(int x, int a, bitset<MX_NF> &y)
{
	for (int i = 0; i < N && NFA_states[x].transitions[a][i] != -1; i++)
	{
		y[NFA_states[x].transitions[a][i]] = 1;
	}
}

// Function 4. Build the bitset showing the set of staes the NFA can
// be in after making a transition from X on input y

void MoveNFA(bitset<MX_NF> x, int a, bitset<MX_NF> &y)
{
	for (int i = 0; i < N; i++)
		if (x[i] == 1)
			MoveNFA(i, a, y);
}

// Main Funtion

int main()
{
	int i, j, X, Y, A, T, F, D;

	//1. Get the input document i.e txt file with the transition table and details

	ifstream fin("NFA.txt");
	fin >> N >> M; // The number of states and The alphabet size
	NFA_states = new NFA_state[N];
	fin >> F; // The number of final states

	for (i = 0; i < F; i++)
	{
		fin >> X;
		NFA_Final.insert(X); // Add the fianl states to the final state list
	}

	fin >> T; // The number of transitions
	while (T--)
	{
		fin >> X >> A >> Y; // The source, alphabet, and the number of states it goes to
		for (i = 0; i < Y; i++)
		{
			fin >> j; // destination state
			NFA_states[X].transitions[A][i] = j; // add Transition on A from X to j
		}
	}
	fin.close();
	// Input complete;

	//2. Build the DFA
	D = 1;
	DF_states.push_back(new DFA_State); // insert new state into the states vector
	DF_states[0]->Const_NFA_states[0] = 1; // add one NFA state that it constitues
	E_Close(0, DF_states[0]->Const_NFA_states); // find its Epsilon closure

	//Check if its the final state or not
	for ( j = 0; j < N; j++)
	{
		if (DF_states[0]->Const_NFA_states[j] == 1 && NFA_Final.find(
		j) != NFA_Final.end()) // Check for final state
		{
			DF_states[0]->is_final = true; // set final to true
			DFA_Final.push_back(0); // add to the finals list
			break;
		}
	}
	to_do_DFA.push(0); // insert the partially checked state into the queue

	while (!to_do_DFA.empty()) // while the partially complete list isn't empty
	{
		X = to_do_DFA.front(); // extract a state
		to_do_DFA.pop(); // remove from queue
		// for each charecter in the alphabet:
		for ( i = 1; i <= M; i++)
		{
			MoveNFA(DF_states[X]->Const_NFA_states, i, DF_states[X]->transitions[i]);
			// Find all set of states the state can reach on 'i' input
			E_Close(DF_states[X]->transitions[i], DF_states[X]->transitions[i]);
			// Find the Epsilon closure of X and get the true transiton list;

			// For X check if X has an overlap i.e merged state with other D DFA states
			for (j = 0; j < D; j++)
			{
				if (DF_states[X]->transitions[i] == DF_states[j]->Const_NFA_states)
				{
					DF_states[X]->symbTrans[i] = j; // create a 'symbolic' link
					break;
				}
			}
			// If J is the last i.e final state in the DFA list
			if (j == D)
			{
				DF_states[X]->symbTrans[i] = D; // add symbolic link to D
				DF_states.push_back(new DFA_State); // add new state into the DFA vector
				DF_states[D]->Const_NFA_states = DF_states[X]->transitions[i];
				for (j = 0; j < N; j++)
				{
					//check if D is the final state, if yes, add it to the final state list
					if (DF_states[D]->Const_NFA_states[j] == 1 && NFA_Final.find(j) != NFA_Final.end())
					{
						DF_states[D]->is_final = true;
						DFA_Final.push_back(D); 
						break;
					}
				}
				to_do_DFA.push(D); // add D to the partially complete list
				D++; // Increase the count of DFA states
			}
		}
	}

	//3. Write the DFA to File

	ofstream fout("DFA.txt");
	// The Number of states, The alphabet and the number of final states.
	fout << D << " " << M << endl <<DFA_Final.size();
	//Write out all final states.
	for (vector<int>::iterator it = DFA_Final.begin(); it != DFA_Final.end(); it++)
	{
		fout << " " << *it;
	}
	fout << endl;
	//Write out all transitions i.e the complete transition table.
	for (i = 0; i < D; i++)
	{
		for (j = 1; j <= M; j++)
		{
			fout << i << " " << j << " " << DF_states[i]->symbTrans[j] << endl;
		}
	}
	fout.close();
	//Output complete
	return 0;
}