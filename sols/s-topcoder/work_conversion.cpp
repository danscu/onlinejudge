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
#include <string>
#include <sstream>
#include <limits>
#include <assert.h>

using namespace std;

#define DBG 0

#if DBG
#define D(x) x;
#else
#define D(x)
#endif

#define CLR(x) memset(x, 0, sizeof x)

const int maxn = 15005;
const int INF = 10000000;
int N;
char g[maxn][maxn];
int dist[maxn][maxn];

double solve() {
	int i, j, k;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++) {
			if (i == j)
				dist[i][j] = 0;
			else
				dist[i][j] = g[i][j] == 0 ? INF : g[i][j];
		}
	for (k=0;k<N;k++)
		for (i=0;i<N;i++)
			for (j=0;j<N;j++)
				dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);

	int sum = 0, cnt = 0;
	for (i=0;i<N;i++) {
		for (j=0;j<N;j++) {
			if (i != j && dist[i][j] < INF) {
				sum += dist[i][j];
				cnt ++;
			}
			D(cout<<dist[i][j]<<" ");
		}
		D(cout<<endl);
	}

	return (double)sum / cnt;
}

int main () {
	int tc, T;
#if BENCH
	freopen("work_conversion.txt", "r", stdin);
#endif
	cin >> T;
	cout.precision(3);

	for (tc = 0; tc < T; tc++)
	{
		N = 0;
		int E;
		cin >> E;
		CLR(g);

		for (int i = 0; i < E; i++) {
			int f, t;
			cin >> f >> t;
			g[f-1][t-1] = 1;
			N = max(t,max(N, f));
		}

		cout << fixed << solve() << endl;
	}

	return 0;
}
