#include<bits/stdc++.h>
#define MX_ST 10
#define MX_AL 10
using namespace std;

int N, M, F;
int dfa[MX_AL][MX_ST];
set<int> Final;

bool CheckAccept(vector<int> S)
{
	int len = S.size();
	cout << "Path : 1->";
	int nxt_state = dfa[S[0]][0];
	cout << nxt_state+1 << "->";
	for (int i = 1; i < len; i++)
	{
		nxt_state = dfa[S[i]][nxt_state];
		cout << nxt_state+1 << "->";
	}
	if (Final.find(nxt_state) != Final.end())
	{
		cout << "X";
		return true;
	}
	cout << "X";
	return false;
}

int main()
{
	cout << "Enter the number of states [<10] : ";
	cin >> N;
	cout << "Enter the alphabet size [<10] : ";
	cin >> M;
	cout << "Enter the number final states [<=" << N << "] : ";
	cin >> F;
	int tmp;
	cout << "Enter the final states : ";
	for (int i = 0; i < F; i++)
	{
		cin >> tmp;
		Final.insert(tmp-1);
	}
	cout << "Enter the transitions" << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			int tmp;
			cout << "Q" << i + 1 << " ";
			cout << j << " = " ;
			cin >> tmp;
			dfa[j][i] = tmp - 1;
		}
	}
	string S;
	cout << "Enter the string : ";
	cin >> S;
	vector<int> V;
	for (int i = 0 ; i < S.length(); i++)
	{
		V.push_back(int(S[i]-'0'));
	}
	if (CheckAccept(V))
		cout << "String is accepted" << endl;
	else
		cout << "String is rejected" << endl;
	return 0;
}
