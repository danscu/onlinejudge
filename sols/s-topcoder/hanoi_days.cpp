#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>
#include <climits>
#include <cfloat>
#include <cmath>
#include <map>
#include <list>
#include <bitset>
#include <cassert>

using namespace std;

#define DBG 0

#if DBG
#define D(x) x;
#else
#define D(x)
#endif

const int maxn = 100000;

int A[maxn]; // day 2
int B[maxn]; // day 3

/**
 * k   - which disc to compare
 * dst - destination of k
 * src - source of k
 */
bool earlyA(int k, int dst, int src) {
	// base
	if (k < 0)
		return false; // equal
	int scoreA = A[k] == src ? 0 : (A[k] == dst ? 2 : 1);
	int scoreB = B[k] == src ? 0 : (B[k] == dst ? 2 : 1);

	if (scoreA < scoreB)
		return true;
	else if (scoreA > scoreB)
		return false;
	else {
		int imm = 3 - dst - src;
		switch (scoreA) {
		case 0:
			return earlyA(k - 1, imm, src);
		case 1:
			return false;
		case 2:
			return earlyA(k - 1, dst, imm);
			break;
		}
	}
}

int main() {
	int T;
	int n;
	int i;

#if BENCH
	freopen("hanoi_days.txt","r",stdin);
#endif

	cin >> T;
	int pos;

	for (int tc = 0; tc < T; tc++) {
		cin >> n;

		// A
		for (i = 0; i < n; i++) {
			cin >> pos;
			A[n - i - 1] = pos - 1;
		}

		// B
		for (i = 0; i < n; i++) {
			cin >> pos;
			B[n - i - 1] = pos - 1;
		}

		cout << "Case #" << tc + 1 << endl;

		cout << earlyA(n - 1, 1, 0) << endl;
	}

	return 0;
}
