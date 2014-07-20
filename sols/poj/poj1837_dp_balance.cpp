/* poj 1837 */
/* dp, 0/1 backsack */

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
const Num maxn = 21;
const Num MAXS = (20 * 25 * 15); // +/-7500
const Num INF = numeric_limits<Num>::max();

int n,m; // n: hooks, m: weights
Num hook[maxn];
Num w[maxn];
Num wsum;
Num dp[maxn+1][MAXS*2+1]; // MAXS*2+1 for both + - and 0 values

#define torq(x) (MAXS + x)

Num solve() {
	const int maxStat = hook[n-1] * wsum;
	const int minStat = hook[0] * wsum;
	dp[0][torq(0)] = 1;
	FOR(i,1,m) // weight
		FOR(j,minStat,maxStat) // torque
			REP(k,n) // hook
				dp[i][torq(j + w[i - 1] * hook[k])] += dp[i-1][torq(j)];
	return dp[m][torq(0)];
}

int main() {
#if BENCH
	freopen("files/poj1837_dp_balance.txt","r",stdin);
#endif
	while (~scanf("%d%d", &n, &m)) {
		CLR(dp);
		REP(i,n)
			scanf("%d", &hook[i]);
		wsum = 0;
		REP(i,m)
			scanf("%d", &w[i]), wsum += w[i];
		printf("%d\n", solve());
	}
	return 0;
}
