/*

In Practice, You should use the statndard input/output
in order to receive a score properly.
Do not use file input and output. Please be very careful.

 */

#include <cstdio>
#include <iostream>

using namespace std;

const int maxn = 100005;
typedef long long Num;

int N,M;
Num dp[maxn];
Num Answer;

int main(int argc, char** argv)
{
	int test_case;
	int T, i;
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
	freopen("domino_tiling.txt", "r", stdin);
#endif
	cin >> T;
	for(test_case = 0; test_case < T; test_case++)
	{
		cin >> N;
		cin >> M;

		/**********************************
		 *  Implement your algorithm here. *
		 ***********************************/
		dp[0] = 1; dp[1] = 1;
		for (i = 2; i <= N; i++) {
			dp[i] = ((dp[i-2]*2) % M + dp[i-1]) % M;
			cout << i << " " << dp[i] << endl;
		}
		Answer = dp[N] % M;

		// Print the answer to standard output(screen).
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}
