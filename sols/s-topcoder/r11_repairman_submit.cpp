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

// open list
int que[maxn*maxn*4][3];
int head, rear;

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

void inline enque(int i, int j, int d) {
	que[rear][0] = i;
	que[rear][1] = j;
	que[rear][2] = d;
	rear++;
}

Num solve() {
	int i,j,d;

	// sort by pos (asc)
	sort(pt, pt+N, byP);

	// init
	memset(dp, -1, sizeof dp);

	// cumultative weights
	Sw[0]=0;

	head=rear=0;

	for (i=0;i<N;i++) {
		dp[i][i][LT] = dp[i][i][RT] = 0;
		enque(i,i,LT);
		enque(i,i,RT);
		Sw[i+1]=Sw[i] + pt[i].w;
	}

	// bfs extend
	while (head<rear) {
		i = que[head][0]; j = que[head][1]; d = que[head][2];
		head++;

		Num ndp;

		// extend (i,j,d)
		if (d == LT) {
			// LT
			if (i > 0) {
				ndp = dp[i][j][LT] + cost(i-1, i, i-1, j);
				if (ndp < dp[i-1][j][LT]) {
					dp[i-1][j][LT] = ndp;
					enque(i-1,j,LT);
				}
			}

			if (j+1 < N) {
				ndp = dp[i][j][LT] + cost(j+1, i, i, j+1);
				if (ndp < dp[i][j+1][RT]) {
					dp[i][j+1][RT] = ndp;
					enque(i,j+1,RT);
				}
			}
		} else {
			// d == RT
			if (j+1 < N) {
				ndp = dp[i][j][RT] + cost(j+1, j, i, j+1);
				if (ndp < dp[i][j+1][RT]) {
					dp[i][j+1][RT] = ndp;
					enque(i,j+1,RT);
				}
			}

			if (i > 0) {
				ndp = dp[i][j][RT] + cost(i-1, j, i-1, j);
				if (ndp < dp[i-1][j][LT]) {
					dp[i-1][j][LT] = ndp;
					enque(i-1,j,LT);
				}
			}
		}
	}

	return min(dp[0][N-1][LT], dp[0][N-1][RT]);
}

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
	}

	return 0;//Your program should return 0 on normal termination.
}
