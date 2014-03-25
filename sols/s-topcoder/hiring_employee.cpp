// In Practice, You should use the statndard input/output
// in order to receive a score properly.
// Do not use file input and output. Please be very careful.

#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

int N;
int Si[300005];
int Fn[32001];

void solve(int N, int *Si) {
	int i;
	memset(Fn, 0, sizeof Fn);
	for (i=0;i<N;i++)
		Fn[Si[i]]++;
	for (i=32000-1;i>=1;i--)
		Fn[i]+=Fn[i+1];
	for (i=0;i<N;i++) {
		int rnk=Fn[Si[i]];
		// adjust for ties
		int upper = Si[i]==32000 ? 0 : Fn[Si[i]+1];
		int ties = Fn[Si[i]] - upper;
		rnk -= ties - 1;
		cout << rnk << " ";
	}
}

int main(int argc, char** argv)
{
	int tc, T, i;

	// The freopen function below opens input.txt file in read only mode, and afterward,
	// the program will read from input.txt file instead of standard(keyboard) input.
	// To test your program, you may save input data in input.txt file,
	// and use freopen function to read from the file when using cin function.
	// You may remove the comment symbols(//) in the below statement and use it.
	// Use #include<cstdio> or #include<stdio.h> to use the function in your program.
	// But before submission, you must remove the freopen function or rewrite comment symbols(//).

	// freopen("input.txt", "r", stdin);

	cin >> T;
	for(tc = 0; tc < T; tc++)
	{
		cin >> N;
		for(i = 0; i < N; i++) {
			cin >> Si[i];
		}

		/**********************************
		*  Implement your algorithm here. *
		***********************************/

		// Print the answer to standard output(screen).
		solve(N, Si);

		cout << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}


