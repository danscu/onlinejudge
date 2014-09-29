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
#define DBG 0 // modify this for enabling/disable debug
#else
#define DBG 0
#endif // BENCH

#define D(...) do { if (DBG) fprintf(stdout, __VA_ARGS__); } while (0)

#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, (n)*sizeof x[0]);
#define CLRVN(x, v, n) memset(x, v, (n)*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
	typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

typedef int Num;
const Num maxn = 1010;
const Num INF = numeric_limits<Num>::max();

int N;
vector<int> g[maxn];

// return cut nodes
int dfs(int u, int par) {
	D("u=%d\n", u);
	int cnt[3] = {};
	for(every(v,g[u])) {
		int j = *v;
		if (j != par) {
			cnt[0] = dfs(j, u);
			sort(cnt,cnt+3);
		}
	}
	return cnt[1] ? cnt[1] + cnt[2] + 1 : 1;
}

int solve() {
	int maxtree = 1;
	FOR(root,1,N) {
		maxtree = max(maxtree, dfs(root, -1));
	}
	return N - maxtree;
}

int main() {
#if BENCH
	freopen("files/gcj141ab_full_tree_large.in","r",stdin);
//	freopen("files/gcj141ab_full_tree_large.out","w",stdout);
#endif
	int T;
	scanf("%d", &T);
	for (int tc = 0; tc < T; tc++) {
		scanf("%d", &N);
		CLR(g);
		REP(i,N-1) {
			int a,b;
			scanf("%d%d", &a, &b);
			g[a].push_back(b);
			g[b].push_back(a);
		}
		printf("Case #%d: ", tc + 1);
		printf("%d\n", solve());
	}
	return 0;
}
