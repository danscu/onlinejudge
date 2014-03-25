#include <iostream>
#include <cstdio>
#include <algorithm>
#include <climits>
#include <cassert>

using namespace std;

#define MAXN 1001

int Answer;
int K, N;    // K - number of stops, N - number of riders
int S[MAXN]; // stops for rider i
int F;       // number of floors

int **m;   // m[i][j]: i=last stopped floor, j=number of stops
int **p;   // parent table

int floors_walked(int prev, int cur) {
	int nsteps = 0;
	int i;

	for (i = 0; i < N; i++)
		if ((S[i] > prev && S[i] <= cur))
			nsteps += min(S[i]-prev, cur-S[i]);

	return nsteps;
}

int solve(int *mincost) {
	int cost = 0;

	int i, j, k;
	int laststop;

	for (i = 0; i <= F; i++) {
		m[i][0] = floors_walked(0, INT_MAX);
		p[i][0] = -1;
	}

	// j stops
	for (j=1; j<=K; j++)
		// last stop at floor i
		for (i=0; i <= F; i++) {
			m[i][j] = INT_MAX;
			// optimize over k
			for (k = 0; k <= i; k++) {
				cost = m[k][j-1] - floors_walked(k, INT_MAX) +
						floors_walked(k, i) + floors_walked(i, INT_MAX);
				if (cost < m[i][j]) {
					m[i][j] = cost;
					p[i][j] = k;
				}
			}
		}

	laststop = 0;
	for (i = 1; i <= F; i++)
		if (m[i][K] < m[laststop][K])
			laststop = i;

	*mincost = m[laststop][K];
	return laststop;
}

void reconstruct_path(int lastfloor, int stops_to_go) {
	if (stops_to_go > 1)
		reconstruct_path(p[lastfloor][stops_to_go], stops_to_go - 1);
	cout << lastfloor << " ";
}

int main(int argc, char** argv)
{
	int test_case;
	int i;

	/*
	   The freopen function below opens input.txt file in read only mode, and afterward,
	   the program will read from input.txt file instead of standard(keyboard) input.
	   To test your program, you may save input data in input.txt file,
	   and use freopen function to read from the file when using cin function.
	   You may remove the comment symbols(//) in the below statement and use it.
	   Use #include<cstdio> or #include<stdio.h> to use the function in your program.
	   But before submission, you must remove the freopen function or rewrite comment symbols(//).
	 */

#if BENCH
	freopen("elevator.txt", "r", stdin);
#endif

	/*
	   Program is given to the problem, test cases should be handled.
                 If a test case is given to 10   ex) test_case < 10
	 */

	int T;
	cin >> T;
	for(test_case = 0; test_case < T; test_case++)
	{

		/*
			Read each test case from standard input.
			The number of node is N[0], N[1], ..., N[9]
		 */

		cin >> K >> N;
		F = 0;

		for (i = 0; i < N; i++) {
			cin >> S[i];
			F = max(F, S[i]);
		}

		m = (int**)malloc(sizeof(int*) * (1 + F));
		p = (int**)malloc(sizeof(int*) * (1 + F));
		for (i = 0; i <= F; i++) {
			m[i] = (int*)malloc(sizeof(int) * (K + 1));
			p[i] = (int*)malloc(sizeof(int) * (K + 1));
			assert(m[i]);
			assert(p[i]);
		}

		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
		   Implement your algorithm here.
		   The answer to the case will be stored in variable Answer.
		 */
		/////////////////////////////////////////////////////////////////////////////////////////////

		int laststop = solve(&Answer);

		// Print the answer to standard output(screen).
		cout << "Case # " << test_case+1;
		cout << endl << Answer << endl;

		reconstruct_path(laststop, K);
		cout << endl;

		// Clean up
		for (i = 0; i <= F; i++) {
			free(m[i]);
			free(p[i]);
		}
		free(m);
		free(p);
	}

	return 0;//Your program should return 0 on normal termination.
}
