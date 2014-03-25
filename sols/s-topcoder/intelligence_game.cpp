#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int maxn = 505;
int n;
char bg[maxn][maxn]; // bipartite graph

// find augpath for bpm
bool augpath(int u, bool seen[], int matchR[]) {
	for (int v = 0; v < n; v++) {
		if (bg[u][v] && !seen[v]) {
			seen[v] = true;
			if (matchR[v] < 0 || augpath(matchR[v], seen, matchR)) {
				matchR[v] = u;
				return true;
			}
		}
	}
	return false;
}

// maximum bipartite matching, returns cardinality
// perfect matching is the minimum edge cover
int maxBpm() {
	int matchR[n];
	memset(matchR, -1, sizeof matchR);

	int cardin = 0;
	for (int u = 0; u < n; u++) {
		bool seen[n];
		memset(seen, 0, sizeof seen);
		if (augpath(u, seen, matchR))
			cardin++;
	}
	return cardin;
}

int main() {
	int T;
	int k, i, x, y;

#if BENCH
	freopen("intelligence_game.txt","r",stdin);
#endif

	cin >> T;
	for (int tc = 0; tc < T; tc++) {
		cin >> n >> k;
		for (i=0;i<n;i++)
			memset(bg[i], 0, sizeof(bg[i][0]) * n);

		for (i=0;i<k;i++) {
			cin >> x >> y;
			x--; y--;
			bg[x][y]++; // edge = star
		}
		cout << maxBpm() << endl;
	}

	return 0;
}
