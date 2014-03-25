// In Practice, You should use the statndard input/output
// in order to receive a score properly.
// Do not use file input and output. Please be very careful.

#include <cstdio>
#include <iostream>
#include <algorithm> // std::min
#include <climits>

using namespace std;

const int MAX=INT_MAX/2;

int N,S;
int data[1005];
int Answer;

int finl_t[1005][1005]; // time
int finr_t[1005][1005];

int finl_c[1005][1005]; // cost (depends on time and number of switches on)
int finr_c[1005][1005];

int cmpfunc(const void *a, const void *b) {
	return ( *(int*)a - *(int*)b );
}

int finr(int m, int n, int *time);

int finl(int m, int n, int *time) {
	// base cases
	if (m<0||n<0||m>=N||n>=N)
		return -1;
	if (finl_c[m][n]!=MAX) {
		*time=finl_t[m][n];
		return finl_c[m][n];
	} else if (m >= n)
		return -1;

	int finlt, finrt;
	int finlc_1 = finl(m + 1, n, &finlt);
	if (finlc_1 != -1)
		finlc_1 += (data[m+1] - data[m]) + finlt;

	int finrc_1 = finr(m + 1, n, &finrt);
	if (finrc_1 != -1)
		finrc_1 += (data[n] - data[m]) + finrt;

	if (finlc_1 == -1 && finrc_1 == -1)
		return -1;

	if (finrc_1 == -1 || finlc_1 <= finrc_1) {
		*time = finlt + (data[m+1] - data[m]);
		finl_t[m][n] = *time;
		return finl_c[m][n]=finlc_1;
	} else {
		*time = finrt + (data[n] - data[m]);
		finl_t[m][n] = *time;
		return finl_c[m][n]=finrc_1;
	}
}

int finr(int m, int n, int *time) {
	// base cases
	if (m<0||n<0||m>=N||n>=N)
		return -1;
	if (finr_c[m][n]!=MAX) {
		*time=finr_t[m][n];
		return finr_c[m][n];
	} else if (m >= n)
		return -1;

	int finrt, finlt;
	int finlc_1 = finl(m, n-1, &finlt);

	if (finlc_1 != -1)
		finlc_1 += (data[n] - data[m]) + finlt;

	int finrc_1 = finr(m, n-1, &finrt);
	if (finrc_1 != -1)
		finrc_1 += (data[n] - data[n-1]) + finrt;

	if (finlc_1 == -1 && finrc_1 == -1)
		return -1;

	if (finrc_1 == -1 || finlc_1 <= finrc_1) {
		*time = finlt + (data[n] - data[m]);
		finl_t[m][n] = *time;
		return finl_c[m][n]=finlc_1;
	} else {
		*time = finrt + (data[n] - data[n-1]);
		finr_t[m][n] = *time;
		return finr_c[m][n]=finrc_1;
	}
}

int solve() {
	// TD: init
	int i,j;
	for (i=0;i<N;i++)
		for (j=0;j<N;j++) {
			finl_c[i][j]=finr_c[i][j]=MAX;
		}

	// better sort S
	qsort(data, N, sizeof(int), cmpfunc);

	// find M,N around S (M may include S)
	int firstM=-1, firstN=-1;
	for (i=0;i<N;i++) {
		if (data[i]<=S)
			firstM=i;
		if (data[i]>S) {
			firstN=i;
			break;
		}
	}

	// base cases
	if (firstM!=-1) {
		finl_t[firstM][firstM]=finl_c[firstM][firstM]=S-data[firstM];
	}

	if (firstN!=-1) {
		finr_t[firstN][firstN]=finr_c[firstN][firstN]=data[firstN]-S;
	}

	int time_l, time_r;
	int l = finl(0, N-1, &time_l);
	int r = finr(0, N-1, &time_r);
	l = l == -1 ? MAX : l;
	r = r == -1 ? MAX : r;
	int total = min(l, r);
	return total;
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

//	freopen("/home/danke/workspace/skymap/src/switchoff.txt", "r", stdin);

	cin >> T;
	for(tc = 0; tc < T; tc++)
	{
		cin >> N >> S;
		for(i=0;i<N;i++) {
			cin >> data[i];
		}

		/**********************************
		*  Implement your algorithm here. *
		***********************************/
		Answer = solve();

		// Print the answer to standard output(screen).
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}


