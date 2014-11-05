/* POJ 1160 Post Office
 * DP + k-optimization
 */
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

#define D(...) do { if (DBG) fprintf(stderr, __VA_ARGS__); } while (0)

#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, (n)*sizeof x[0]);
#define CLRVN(x, v, n) memset(x, v, (n)*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
	typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

typedef int Num;
const Num maxn = 305;
const Num INF = 1000000000;

int V,P;
Num sum[maxn][maxn]; // min cost for building a post office between i and j
Num pos[maxn];
Num dp[maxn][maxn];  // cost to build j post offices in first i villages
int K[maxn][maxn];

/*
 * dp[i][j] = min_k { dp[k][j-1] + sum[k+1][i] }
 *
 * sum[i][j] = sum[i][j-1] + p[j] - p[(i+j)/2] -- draw a diagram and derive
 *
 * K[i][j-1] <= k <= K[i+1][j] : where K[i][j] = argmin_k { dp[k][j-1] + sum[k+1][i] }
 */

Num solve() {
	FOR(i,1,V) {
		FOR(j,i+1,V)
			sum[i][j] = sum[i][j-1] + pos[j] - pos[(i+j)/2];
		dp[i][1] = sum[1][i];
		dp[i][i] = 0;
		K[i][1] = 0;
	}

	FOR(j,2,P) {
		K[V+1][j] = V;
		for(int i = V; i > j; i--)
			FOR(k, K[i][j-1], K[i+1][j]) {
				if (dp[k][j-1] + sum[k+1][i] < dp[i][j]) {
					dp[i][j] = dp[k][j-1] + sum[k+1][i];
					K[i][j] = k;
				}
		}
	}

#if DBG
	FOR(i,0,V) {
		FOR(j,0,P)
			cout << dp[i][j] << " ";
		cout << endl;
	}
#endif

	return dp[V][P];
}

int main() {
#if BENCH
	freopen("files/poj1160_post_office.txt","r",stdin);
#endif
	while (~scanf("%d%d", &V, &P)) {
		REP(i,V+1)
			REP(j,V+1) {
				dp[i][j] = INF;
				sum[i][j] = 0;
			}
		pos[0] = 0;

		FOR(v,1,V)
			scanf("%d", &pos[v]);

		printf("%lld\n", solve());
	}
	return 0;
}
