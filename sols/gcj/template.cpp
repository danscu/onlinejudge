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

typedef long long Num;
const int maxn=801;
int N;

Num data[maxn];

Num solve() {
	return 0;
}

int main() {
	// input
	string basename("a-large");
	string in(basename + ".in");
	string out(basename + ".out");
#if BENCH
	freopen(in.c_str(), "r", stdin);
	if (0) // write to file
		freopen(out.c_str(), "w", stdout);
#endif
	int TC, tc, i;
	cin >> TC;
	for (tc = 0; tc < TC; tc++) {
		cin >> N;
		for(i = 0; i < N; i++)
			cin >> data[i];
		cout << "Case #" << (tc + 1) << ": " << solve() << endl;
	}
	return 0;
}
