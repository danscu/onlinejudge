#include <iostream>
#include <cstdio>

using namespace std;

#define MAXN 128

int Answer;
int N, M;

#define MOD 100000007ULL
typedef unsigned long long Num;
typedef Num Mat[MAXN][MAXN];

Mat power[32]; // power[k] = A^k

void identity(int n, Mat dest) {
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			dest[i][j] = i == j ? 1 : 0;
}

void matCopy(int n, Mat dest, Mat src) {
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			dest[i][j] = src[i][j];
}

void multiply(int n, Mat prod, Mat a, Mat b) {
	int i, j, k;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) {
			Num sum = 0;
			for (k = 0; k < n; k++)
				sum = (sum + a[i][k] * b[k][j] % MOD) % MOD;
			prod[i][j] = sum;
		}
}

void calcPower(int n, Mat prod, Mat a, int m) {
	Mat lastProd;
	identity(n, lastProd);

	int i = 1;
	while (m) {
		// compute current power i
		if (i == 1)
			matCopy(n, power[1], a);
		else
			multiply(n, power[i], power[i-1], power[i-1]);
		if (m & 1) {
			multiply(n, prod, lastProd, power[i]);
			matCopy(n, lastProd, prod);
		}
		m >>= 1;
		i++;
	}
}

int main(int argc, char** argv)
{
	int test_case;
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
    freopen("matrix_multiplication.txt", "r", stdin);
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

		cin >> N >> M;

		// read matrix a
		Mat a;
		int i, j;
		for (i = 0; i < N; i++)
			for (j = 0; j < N; j++)
				cin >> a[i][j];

		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
		   Implement your algorithm here.
		   The answer to the case will be stored in variable Answer.
		 */
		/////////////////////////////////////////////////////////////////////////////////////////////
		Mat prod;
		calcPower(N, prod, a, M);

		// Print the answer to standard output(screen).
		cout << "Case# " << test_case + 1 << endl;
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++)
				cout << prod[i][j] << " ";
			cout << endl;
		}
	}

	return 0;//Your program should return 0 on normal termination.
}
