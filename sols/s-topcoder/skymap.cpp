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

int N;
int data[26][26];

int color(int n, int m[26][26], int x, int y, int sz) {
	static const int dx[] = {1, -1, 0, 0};
	static const int dy[] = {0, 0, 1, -1};

	m[x][y] = 2;

	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (nx >= 0 && ny >= 0 && nx < n && ny < n) {
			if (m[nx][ny] == 1)
				sz += color(n, m, nx, ny, 1);
		}
	}

	return sz;
}

void solve(int n, int m[26][26], int *S, int *C) {
	int maxsize = 0;
	int blocks = 0;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (m[i][j] == 1) {
				int size = color(n, m, i, j, 1);
				blocks++;
				maxsize = max(maxsize, size);
			}
		}

	*S = blocks;
	*C = maxsize;
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
	// freopen("input.txt", "r", stdin);

	cin >> T;
	for(test_case = 0; test_case < T; test_case++)
	{
		int i,j;
		int S,C;
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

		S = 0;
		C = 0;

		solve(N, data, &S, &C);

		// Print the answer to standard output(screen).
		cout << S << " " << C << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}


