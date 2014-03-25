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

using namespace std;

#define DBG 0

#if DBG
#define D(x) x;
#else
#define D(x)
#endif

const int maxn = 1005;
typedef unsigned Num; // must be unsigned

#define LT 0
#define RT 1

struct Loc {
	int p;
	int w;
};

bool byP(const Loc& a, const Loc& b) {
	return a.p < b.p;
}

int N;
Loc pt[maxn];
int Sw[maxn+1]; // Sw[i+1] = Sum_k>=i w_k
Num dp[maxn][maxn][2]; // mincost

#if DBG
pair<int,int> parent[maxn][maxn][2];
#endif

Num cost(int to, int from, int curi, int curj) {
	int dist = abs(pt[to].p - pt[from].p);
	int left = min(to, curi);
	int right = max(to, curj);

	int c = Sw[left] + Sw[N] - Sw[right+1];

	// to has not been visited
	c += pt[to].w;

	c *= dist;
	return c;
}

pair<int,int> make_node(int i, int j, int d) {
	return make_pair(i*2+d,j);
}

Num solve() {
	int i,j,d;

	// sort by pos (asc)
	sort(pt, pt+N, byP);

	list<pair<int,int> > open;

	// init
	memset(dp, -1, sizeof dp);

	// cumultative weights
	Sw[0]=0;

	for (i=0;i<N;i++) {
		dp[i][i][LT] = dp[i][i][RT] = 0;
		open.push_back(make_node(i,i,LT));
		open.push_back(make_node(i,i,RT));
		Sw[i+1]=Sw[i] + pt[i].w;
	}

	// bfs extend
	while (!open.empty()) {
		pair<int,int> cur = open.front(); open.pop_front();
		i = cur.first / 2; j = cur.second; d = cur.first % 2;

		Num ndp;

		// extend (i,j,d)
		if (d == LT) {
			// LT
			if (i > 0) {
				ndp = dp[i][j][LT] + cost(i-1, i, i-1, j);
				if (ndp < dp[i-1][j][LT]) {
					dp[i-1][j][LT] = ndp;
					open.push_back(make_node(i-1,j,LT));
					D(parent[i-1][j][LT] = make_node(i,j,d));
				}
			}

			if (j+1 < N) {
				ndp = dp[i][j][LT] + cost(j+1, i, i, j+1);
				if (ndp < dp[i][j+1][RT]) {
					dp[i][j+1][RT] = ndp;
					open.push_back(make_node(i,j+1,RT));
					D(parent[i][j+1][RT] = make_node(i,j,d));
				}
			}
		} else {
			// d == RT
			if (j+1 < N) {
				ndp = dp[i][j][RT] + cost(j+1, j, i, j+1);
				if (ndp < dp[i][j+1][RT]) {
					dp[i][j+1][RT] = ndp;
					open.push_back(make_node(i,j+1,RT));
					D(parent[i][j+1][RT] = make_node(i,j,d));
				}
			}

			if (i > 0) {
				ndp = dp[i][j][RT] + cost(i-1, j, i-1, j);
				if (ndp < dp[i-1][j][LT]) {
					dp[i-1][j][LT] = ndp;
					open.push_back(make_node(i-1,j,LT));
					D(parent[i-1][j][LT] = make_node(i,j,d));
				}
			}
		}
	}

	return min(dp[0][N-1][LT], dp[0][N-1][RT]);
}

#if DBG
void track_path(int i, int j, int d) {
	if (i != j) {
		pair<int,int> &t = parent[i][j][d];
		track_path(t.first/2, t.second, t.first%2);
	}
	cout << i << "," << j << "," << d << " " << dp[i][j][d] << endl;
}
#endif

int main(int argc, char** argv)
{
	int tc, T, i;

#if BENCH
	freopen("repairman.txt", "r", stdin);
#endif

	cin >> T;
	for(tc = 0; tc < T; tc++)
	{
		cin >> N;
		for(i=0;i<N;i++)
			cin >> pt[i].p;
		for(i=0;i<N;i++)
			cin >> pt[i].w;

		/**********************************
		*  Implement your algorithm here. *
		***********************************/
		Num Answer = solve();

		// Print the answer to standard output(screen).
		cout << "Case #" << tc + 1 << endl << Answer << endl;

#if DBG
		int j;
		for (i=0;i<N;i++) {
			cout << "i=" << i << "  ";
			for (j=0;j<N;j++) {
				cout << (signed)dp[i][j][0] << ":" << (signed)dp[i][j][1] << " ";
			}
			cout << endl;
		}

		if (dp[0][N-1][LT] < dp[0][N-1][RT])
			track_path(0, N-1, LT);
		else
			track_path(0, N-1, RT);
#endif
	}

	return 0;//Your program should return 0 on normal termination.
}
