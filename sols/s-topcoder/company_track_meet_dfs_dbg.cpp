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

const int maxn = 70;
const int INF = 1000000;

int n;
int rank[maxn];

list<int> cand;
int minCost, minCnt;

#if DBG
int depth;
int match[maxn][2];
#endif

int dfs(list<int>::iterator it, int cost, int idx, int dep) {
	// base
	if (it == cand.end()) {
		if (cand.size() == 1) {
			if (cost < minCost) {
				minCost = cost;
				minCnt = 1;
			} else if (cost == minCost)
				minCnt++;
#if DBG
			if (cost == minCost) {
				cout << "Solution " << minCnt << " @ " << cost << endl;
				for (int i = 0; i < dep; i++) {
					cout << match[i][0] << " " << match[i][1] << endl;
				}
			}
#endif
			return cost;
		}
		return INF;
	}

	// cut
	if (cost >= minCost)
		return INF;

	// end of row
	list<int>::iterator next(it); next++;
	if (next == cand.end())
		return dfs(next, cost, idx + 1, dep);

	// remove higher
	int dcost = abs(*it - *next);
	int removedItem;
	list<int>::iterator remIt, nextDfs;

#if DBG
	match[dep][0] = *it; match[dep][1] = *next;
#endif

	list<int>::iterator prev = it; prev--;

	if (*it > *next) {
		removedItem = *it;
		remIt = cand.erase(it);
	} else {
		removedItem = *next;
		remIt = cand.erase(next);
	}

	int localCost = dfs(prev, cost + dcost, idx - 1, dep + 1);

	// restore
	cand.insert(remIt, removedItem);

	// by itself
	localCost = min(localCost, dfs(next, cost, idx + 1, dep));

	return localCost;
}

int solve() {
	cand.clear();
	cand.insert(cand.begin(), rank, rank+n);
	minCost = INF; minCnt = 0;
	return dfs(cand.begin(), 0, 0, 0);
}

int main() {
	int T, i;

#if BENCH
	freopen("company_track_meet.txt","r",stdin);
#endif

	cin >> T;
	for (int tc = 0; tc < T; tc++) {
		cin >> n;
		for (i=0;i<n;i++)
			cin >> rank[i];

		int ans = solve();
		cout << ans << endl;
		cout << minCnt << endl;
		cout << endl;
	}

	return 0;
}
