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

using namespace std;

#define DEBUG 0
#if DEBUG
#define D(x...) printf(x)
#else
#define D(x...)
#endif

int N;
int data[256][256];

// These include the current number [i][j] or numbers to the right or below
int X[256][256];       // length
int H[256][256][256];  // head value

#if DEBUG
string S[256][256][256];
#endif

int solve() {
	int i,j;

	for (i=N-1;i>=0;i--)
		for (j=N-1;j>=0;j--) {
			// search
			int cur = data[i][j];
			int u;

			// copy X/H[i][j+1] into X/H[i][j]
			if (j==N-1) {
				// init to single element
				X[i][j] = 1;
				H[i][j][1] = cur;
#if DEBUG
				ostringstream conv;
				conv << cur;
				S[i][j][1] = conv.str();
#endif
			} else {
				X[i][j] = X[i][j+1];

				// copy X/H[i][j+1]
				for (u=X[i][j+1];u>0;u--) {
					H[i][j][u] = H[i][j+1][u];
#if DEBUG
					S[i][j][u] = S[i][j+1][u];
#endif
				}
			}

			// merge X/H[i+1][j] into X/H[i][j]
			if (i+1<N) {
				X[i][j] = max(X[i][j], X[i+1][j]);

				// merge X/H[i+1][j]
				for (u=X[i+1][j];u>0;u--) {
#if DEBUG
					if (H[i][j][u] < H[i+1][j][u])
						S[i][j][u] = S[i+1][j][u];
#endif
					H[i][j][u] = max(H[i][j][u], H[i+1][j][u]);
				}
			}

			// merge cur (using X[i+1][j+1])

			// cur is a sole item
#if DEBUG
			if (H[i][j][1] < cur) {
				ostringstream conv;
				conv << cur;
				S[i][j][1] = conv.str();
			}
#endif
			H[i][j][1] = max(H[i][j][1], cur);

			if (i+1<N && j+1<N) {
				for (u=X[i+1][j+1];u>0;u--)
					if (cur <= H[i+1][j+1][u]) {
						if (X[i][j] < u+1) {
							H[i][j][u+1] = cur;
							X[i][j] = u+1;
#if DEBUG
							ostringstream conv;
							conv << cur << " ";
							conv << S[i+1][j+1][u];
							S[i][j][u+1] = conv.str();
#endif
						}
						else {
#if DEBUG
							if (H[i][j][u+1] < cur) {
								ostringstream conv;
								conv << cur << " ";
								conv << S[i+1][j+1][u];
								S[i][j][u+1] = conv.str();
							}
#endif
							H[i][j][u+1] = max(H[i][j][u+1], cur);
						}
					}
			}
		}

	return X[0][0];
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("partial_seq.txt", "r", stdin);

	cin >> T;
	for(test_case = 0; test_case < T; test_case++)
	{
		int i,j;
		cin >> N;

		memset(data, 0, sizeof data);
		memset(X, 0, sizeof X);
		memset(H, 0, sizeof H);

		for(i=0; i<N; i++) {
			for(j=0; j<N; j++) {
				cin >> data[i][j];
			}
		}

		/**********************************
		 * Implement your algorithm here. *
		 **********************************/
		int L = solve();

		// Print the answer to standard output(screen).
		cout << L << endl;

#if DEBUG
		cout << S[0][0][L] << endl;
		for (i=0;i<N;i++) {
			for (j=0;j<N;j++)
				cout << X[i][j] << " ";
			cout << endl;
		}
#endif
	}

	return 0;//Your program should return 0 on normal termination.
}
