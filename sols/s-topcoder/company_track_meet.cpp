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
#include <queue>

using namespace std;

#define DBG 0

#if DBG
#define D(x) x;
#else
#define D(x)
#endif

#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)

const int maxn = 70;
const int INF = 1000000;

int n;
int rank[maxn];

int dp[]

int minCost, minCnt;

int solve() {
	cand.insert(cand.begin(), rank, rank+n);
	minCost = INF; minCnt = 0;
	return dfs(cand.begin(), 0);
}

int main() {
	int T;
	int i;

#if BENCH
	freopen("company_track_meet.txt","r",stdin);
#endif

	cin >> T;
	for (int tc = 0; tc < T; tc++) {
		cin >> n;
		for (i=0;i<n;i++) {
			cin >> rank[i];
		}

		int ans = solve();
		cout << ans << endl;
		cout << minCnt << endl;
		cout << endl;
	}

	return 0;
}
