#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>
#include <climits>
#include <cfloat>
#include <cmath>
#include <map>
#include <list>
#include <fstream>

using namespace std;
#ifdef BENCH
#define DBG 1

#if DBG
#define D(x) x;
#else
#define D(x)
#endif
#endif // BENCH

#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, n*sizeof x[0]);
#define CLRVN(x, v, n) memset(x, v, n*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
	typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

typedef int Num;
const int maxn=51;
int N;

Num data[maxn * 2][maxn];
Num map[maxn][maxn];

bool dataUsed[maxn*2];

void solve() {
	int mini = 0;
	REP(i, 2*N-1) {
		if (data[i][0] < data[mini][0])
			mini = i;
	}

	REP(i, N)
	    CLRVN(map[i], -1, N);

	CLRN(dataUsed, 2*N-1);

	REP(k, N) {
		int minr = 9999, minc = 9999;
		int minri, minci;
		REP(i, 2*N-1) {
			if (dataUsed[i]) continue;
			if (data[i][k] < minr) {
				minr = data[i][k];
				minri = i;
			}
			if (data[i][k] < minc) {
				minr = data[i][k];
				minri = i;
			}
		}
	}
}

int main() {
	// input
	string basename("B-small");
	string in(basename + ".in");
	string out(basename + ".out");
#if BENCH
	freopen(in.c_str(), "r", stdin);
	if (0) // write to file
		freopen(out.c_str(), "w", stdout);
#endif
	int TC, tc, i, j;
	cin >> TC;
	for (tc = 0; tc < TC; tc++) {
		cin >> N;
		for (i = 0; i < 2 * N - 1; i++) {
			for (j = 0; j < N; j++)
				cin >> data[i][j];
		}
		cout << "Case #" << (tc + 1) << ": ";
		solve();
		cout << endl;
	}
	return 0;
}
