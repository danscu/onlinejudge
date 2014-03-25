/*

In Practice, You should use the statndard input/output
in order to receive a score properly.
Do not use file input and output. Please be very careful.

*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>

#define DEBUG 1
#if DEBUG
#define D(x...) printf(x)
#else
#define D(x...)
#endif

using namespace std;

int N;
int data[256][256];

int L[256][256];

#if DEBUG
string S[256][256];
int maxI, maxJ;
#endif

int solve() {
	int i,j,x,y;

	for (i=0;i<N;i++) {
		L[N-1][i] = 1;
#if DEBUG
		ostringstream conv;
		conv << data[N-1][i];
		S[N-1][i] = conv.str();
#endif
	}

	int globalL = 0;

	for (i=N-2;i>=0;i--)
		for (j=N;j>0;j--) {
			// search
			int maxL = 1;
			int cur = data[i][j];

#if DEBUG
			ostringstream conv;
			conv << cur;
			S[i][j] = conv.str();
#endif

			for (x=i+1;x<N;x++)
				for (y=j+1;y<N;y++)
					if (cur<=data[x][y])
						if (maxL<1+L[x][y]) {
							maxL=1+L[x][y];
#if DEBUG
							ostringstream conv;
							conv << cur << " ";
							conv << S[x][y];
							S[i][j] = conv.str();
#endif
						}
			L[i][j]=maxL;

			if (globalL < maxL) {
				globalL = maxL;
#if DEBUG
				maxI = i; maxJ = j;
#endif
			}
		}

	return globalL;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	/*
	   The freopen function below opens input.txt file in read only mode, and afterward,
	   the program will read from input.txt file instead of standard(keyboard) input.
	   To test your program, you may save input data in input.txt file,
	   and use freopen function to read from the file when using cin function.
	   You may remove the comment symbols(//) in the below statement and use it.
	   Use #include<cstdio> or #include<stdio.h> to use the function in your program.
	   But before submission, you must remove the freopen function or rewrite comment symbols(//).
	*/
	freopen("/home/danke/workspace/skymap/src/partial_seq.txt", "r", stdin);

	cin >> T;
	for(test_case = 0; test_case < T; test_case++)
	{
		int i,j;
		cin >> N;

		memset(data, 0, sizeof data);

		for(i=0; i<N; i++) {
			for(j=0; j<N; j++) {
				cin >> data[i][j];
			}
		}

		/**********************************
		 * Implement your algorithm here. *
		 **********************************/
		int l = solve();

		// Print the answer to standard output(screen).
		cout << l << endl;

		// Print seq
#if DEBUG
		cout << S[maxI][maxJ] << endl;
		
		for (i=0;i<N;i++) {
			for (j=0;j<N;j++)
				cout << L[i][j] << " ";
			cout << endl;
		}
#endif
	}

	return 0;//Your program should return 0 on normal termination.
}
