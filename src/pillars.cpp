#include <algorithm>
#include <cassert>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

#ifdef BENCH
#define DBG 1 // modify this for enabling/disable debug
#else
#define DBG 0
#endif // BENCH

#define D(...) do { if (DBG) fprintf(stderr, __VA_ARGS__); } while (0)

#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, (n)*sizeof x[0]);
#define CLRVN(x, v, n) memset(x, v, (n)*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
	typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

typedef int Num;
const Num maxn = 105;
const Num INF = numeric_limits<Num>::max();

int n;
Num data[maxn];

struct Node {
	int diff;
	int height;
};

Node nodes[maxn][maxn];

// params are inclusive
Num solve(int s, int e) {
	// cache
	if (nodes[s][e].height >= 0)
		return nodes[s][e];

	Node r;

	if (s == e) {
		r.diff = data[s];
		r.height = data[s];
	} else {
		for (int i = s; i <= e; i++) {
			Node left = solve(s, i);
			Node right = solve(i + 2, e);

			if ()
			r.diff =
		}
	}

	return r;
}

Num solve() {
	memset(nodes, -1, sizeof(nodes));
	return solve(0, n - 1);
}

int main() {
#if BENCH
	freopen("pillars.txt","r",stdin);
#endif
	int T;
	Num i, j;

	scanf("%d", &n);
	REP(i,n) {
		scanf("%d", &data[i]);
	}

	printf("%d\n", solve());

	return 0;
}
