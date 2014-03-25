#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

#define DBG 0
#define VERIFY 0

#define MAXN 600008
#define MAXP 20008

int Answer;
int N, P;

typedef unsigned long long Num;
Num num[MAXN]; // base = 1
Num s[MAXN];

int rem[MAXP]; // rem[i] = # of s[i] elements, st. s[i] mod P == i

void cumulativeSum() {
	int i;
	s[0] = 0;
	for (i = 1; i <= N; i++)
		s[i] = s[i - 1] + num[i];
}

int solve_slow() {
	cumulativeSum();

	int cnt = 0;

	// brutal force
	int i, j;
	for (i = 1; i <= N; i++)
		for (j = i; j <= N; j++) { // inclusive
			Num sumij = s[j] - s[i - 1];
			if (sumij % P == 0)
				cnt++;
		}

	return cnt;
}

// optimized for O(N)
int solve() {
	cumulativeSum();

	memset(rem, 0, sizeof rem);

	int cnt = 0;

	int i; // ending index
	for (i = 1; i <= N; i++) {
		Num remi = s[i] % P;
		if (remi == 0)
			cnt++; // self

		cnt += rem[remi]; // subsequence Sk...Si
		rem[remi]++;
	}

	return cnt;
}

#if !(VERIFY)
int main(int argc, char** argv)
{
	int test_case;

#if BENCH
	freopen("divisible_p.txt", "r", stdin);
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

		cin >> N >> P;

		int i;
		for (i = 1; i <= N; i++) {
			Num val;
			cin >> val;
			num[i] = val % P;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
		   Implement your algorithm here.
		   The answer to the case will be stored in variable Answer.
		 */
		/////////////////////////////////////////////////////////////////////////////////////////////
		Answer = solve();
//		Answer = solve_slow();

		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;

#if DBG
		for (i = 1; i <= N; i++)
			cout << num[i] << " ";
		cout << endl;
#endif

		cout << Answer << endl;
	}

	return 0;
}

#else
int main(int argc, char** argv)
{
	srand(time(NULL));
	int T = 1000;
	bool fail = false;
	for (int tc = 0; tc < T; tc++) {
		N = 2 + rand() % 5001;
		P = 1 + rand() % 103;
		int i;
		for (i = 1; i <= N; i++)
			num[i] = rand() % 1000001;
		int ans1, ans2;
		ans1 = solve_slow();
		ans2 = solve();
		cout << tc << " " << (ans1 == ans2 ? "ok" : "wrong!") << endl;
		fail |= ans1 != ans2;
	}

	cout << (fail ? "fail" : "still_ok") << endl;
	return 0;
}
#endif
