#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <list>

using namespace std;

const int maxn = 70;
const int INF = 1000000;

int n;
int rank[maxn];

list<int> cand;
int minCost, minCnt;

int dfs(list<int>::iterator it, int cost, int dep) {
	// base
	if (it == cand.end()) {
		if (cand.size() == 1) {
			if (cost < minCost) {
				minCost = cost;
				minCnt = 1;
			} else if (cost == minCost)
				minCnt++;
			return cost;
		}
		return INF;
	}

	// by itself
	list<int>::iterator next(it); next++;
	int localCost = dfs(next, cost, dep);

	if (next == cand.end())
		return localCost;

	// remove higher
	int dcost = abs(*it - *next);
	int removedItem;
	list<int>::iterator remIt, nextDfs;

	list<int>::iterator prev = it; prev--;

	if (*it > *next) {
		removedItem = *it;
		remIt = cand.erase(it);
	} else {
		removedItem = *next;
		remIt = cand.erase(next);
	}

	localCost = min(localCost, dfs(prev, cost + dcost, dep + 1));

	// restore
	cand.insert(remIt, removedItem);

	return localCost;
}

int solve() {
	cand.clear();
	cand.insert(cand.begin(), rank, rank+n);
	minCost = INF; minCnt = 0;
	return dfs(cand.begin(), 0, 0);
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
		cout << solve() << endl << minCnt << endl << endl;
	}
	return 0;
}
