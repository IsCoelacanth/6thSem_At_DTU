#include<bits/stdc++.h>
#define MX_N 10
#define MX_A 10
using namespace std;
// Representation of an NFA state
class NFAstate {
public:
	int transitions[MX_A][MX_N];
	NFAstate() {
		for (int i = 0; i<MX_A; i++)
			for (int j = 0; j<MX_N; j++)
				transitions[i][j] = -1;
	}
} *NFAstates;
set <int> NFA_finalStates;
bitset <MX_N> currentStates;
char input_string[100000];
int N;
// finds the epsilon closure of the NFA state "state" and stores it into "closure"
void epsilonClosure(int state, bitset<MX_N> &closure) {
	for (int i = 0; i<N && NFAstates[state].transitions[0][i] != -1; i++)
		if (closure[NFAstates[state].transitions[0][i]] == 0) {
			closure[NFAstates[state].transitions[0][i]] = 1;
			epsilonClosure(NFAstates[state].transitions[0][i], closure);
		}
}
// finds the epsilon closure of a set of NFA states "state" and stores it into "closure"
void epsilonClosure(bitset<MX_N> state, bitset<MX_N> &closure) {
	for (int i = 0; i<N; i++)
		if (state[i] == 1)
			epsilonClosure(i, closure);
}
// returns a bitset representing the set of states the NFA could be in after moving
// from state X on input symbol A
void NFAmove(int X, int A, bitset<MX_N> &Y) {
	for (int i = 0; i<N && NFAstates[X].transitions[A][i] != -1; i++)
		Y[NFAstates[X].transitions[A][i]] = 1;
}
// returns a bitset representing the set of states the NFA could be in after moving
// from the set of states X on input symbol A
void NFAmove(bitset<MX_N> X, int A, bitset<MX_N> &Y) {
	bitset<MX_N> tmp;
	for (int i = 0; i<N; i++)
		if (X[i] == 1)
			NFAmove(i, A, tmp);
	Y = tmp;
}
int main() {
	int M, F, X, Y, A, i, j, T, symbol;
	char* p;
	// read in the underlying NFA
	ifstream fin("NFA.txt");
	fin >> N >> M;
	NFAstates = new NFAstate[N];
	fin >> F;
	for (i = 0; i<F; i++) {
		fin >> X;
		NFA_finalStates.insert(X);
	}
	fin >> T;
	while (T--) {
		fin >> X >> A >> Y;
		for (i = 0; i<Y; i++) {
			fin >> j;
			NFAstates[X].transitions[A][i] = j;
		}
	}
	fin.close();
	// simulate the NFA
	printf("Enter a string ('.' to exit) : ");
	scanf("%[^\n]%*c", input_string);
	while (input_string[0] != '.') {
		currentStates[0] = 1;
		epsilonClosure(currentStates, currentStates);
		p = strtok(input_string, " ");
		while (p) {
			symbol = atoi(p);
			if (symbol <= 0 || symbol > M) {
				printf("Invalid input symbol %d.\n", symbol);
				return -1;
			}
			else {
				NFAmove(currentStates, symbol, currentStates);
				epsilonClosure(currentStates, currentStates);
			}
			p = strtok(NULL, " ");
		}
		for (i = 0; i < N; i++)
			if (currentStates[i] == 1 && NFA_finalStates.find(i) != NFA_finalStates.end())
				break;
		if (i < N)
			printf("String accepted.\n");
		else
			printf("String rejected.\n");
		printf("Enter a string ('.' to exit) : ");
		scanf("%[^\n]%*c", input_string);
	}
	return 0;
}