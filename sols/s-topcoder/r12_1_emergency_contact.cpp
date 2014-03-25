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

# define DBG 0
# if DBG
#  define D(x) x;
# else
#  define D(x)
# endif

#define CLR(x) memset(x, 0, sizeof x);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#endif // BENCH

#define CLRN(x, n) memset(x, 0, n*sizeof x[0]);
typedef int Num;
const int maxw = 20;
const int maxm = 7000;
#define INF 10000000

Num W, M;
Num h[maxw+maxm];
Num w[maxw][maxm]; // cost
vector<pair<Num,Num> > es; // selected edge

bool intersect(int w1, int m1, int w2, int m2) {
	int p11 = h[w1], p12 = h[m1];
	int p21 = h[w2], p22 = h[m2];

	int q11 = min(p11, p12), q12 = max(p11, p12);
	int q21 = min(p21, p22), q22 = max(p21, p22);

	return (q11 < q21 && q21 < q12 && !(q11 <= q22 && q22 <= q12)) ||
			(q11 < q22 && q22 < q12 && !(q11 <= q21 && q21 <= q12));
}

// form intersection?
bool valid(int i, int j) {
	for (vector<pair<Num,Num> >::iterator it = es.begin(); it != es.end(); ++it) {
		int w = it->first, m = it->second;
		if (intersect(w, m, i, j))
			return false;
	}
	return true;
}

int prim() {
	int nodes = M + W;
	int selected[nodes], i, j, edges;
	int min, x, y, v, total = 0;

	for (i = 0; i < nodes; i++)
		selected[i] = false;

	es.clear();
	es.reserve(nodes-1);

	selected[0] = true;
	edges = 0;

	while (edges < nodes - 1) {
		min = INF;
		for (i = 0; i < W + M; i++)
		{
			// i = woman, j = man
			if (i < W && selected[i]) {
				for (j = W; j < nodes; j++) {
					if (!selected[j] && valid(i,j)) {
						if (min > w[i][j-W]) {
							min = w[i][j-W];
							x = i;
							y = j-W;
							v = j;
						}
					}
				}
			}
			// i = man, j = woman
			if (i >= W && selected[i]) {
				for (j = 0; j < W; j++) {
					if (!selected[j] && valid(j,i)) {
						if (min > w[j][i-W]) {
							min = w[j][i-W];
							x = j;
							y = i-W;
							v = j;
						}
					}
				}
			}
		}
		// (x, y) is a minimal edge in I_1 intersect I_2
		selected[v] = true;
		total += w[x][y];
		es.push_back(make_pair(x,W+y));
#if DBG
		cout << x + 1 << " <--> " << W + y + 1
				<< " cost: " << w[x][y] << " total: " << total << endl;
#endif
		edges++;
	}
	return total;
}

#if DBG
void dump() {
	int i,j;
	// print sth.
	for (i = 0; i < W + M; i++)
		cout << h[i] << " ";
	cout << endl;
	for (i = 0; i < W; i++) {
		for (j = 0; j < M; j++)
			cout << w[i][j] << " ";
		cout << endl;
	}

	// sanity test
	for (i = 0; i < W + M - 1; i++) {
		for (j = i + 1; j < i + 1 + M + W; j++) {
			cout << "intersect(0, 3, " << i << ", " << j % (M+W) << ") = " <<
					intersect(0, 3, i, j % (M+W)) << endl;
		}
	}
}
#endif

void solve() {
#if DBG
	dump();
#endif
	int cost = prim();
	cout << cost << endl;
}

struct Node {
	Node *parent;
	Num x, y;
	int size;
};

#define MAXQ 1000000
Node que[MAXQ];
int qh, qr;
int minCost;

void queueE(Node *parent, Num x, Num y, int size) {
	que[qh].parent = parent;
	que[qh].x = x;
	que[qh].y = y;
	que[qh].size = size;
	qh++;
	if (qh == MAXQ)
		qh = 0;
	if (qh == qr)
		assert(false);
}

Node *popQ() {
	Node *p = &que[qr];
	if (++qr == MAXQ)
		qr = 0;
	return p;
}

bool loop(Node *cur, int x, int y, bool newX) {
	if (newX && cur->x == x || !newX && cur->y == y ||
			intersect(x, y, cur->x, cur->y))
		return true;
	if (cur->parent)
		return loop(cur->parent, x, y, newX);
	return false;
}

int findCost(Node *cur) {
	int cost = w[cur->x][cur->y-W];
	if (cur->parent)
		cost += findCost(cur->parent);
	return cost;
}

void solveBrute() {
	int i, j;
	qh = 0, qr = 0;
	for (i = 0; i < W; i++) {
		for (j = 0; j < M; j++)
			queueE(0, i, j + W, 1);
	}

	minCost = INT_MAX;
	while (qr != qh) {
		Node *cur = popQ();
		if (cur->size == M + W - 1) {
			int cost = findCost(cur);
			minCost = min(cost, minCost);
		}
		for (i = 0; i < W + M; i++)
		{
			// i = woman, j = man
			if (i < W) {
				for (j = W; j < M + W; j++) {
					if (!loop(cur, cur->x, j, false))
						queueE(cur, cur->x, j, cur->size + 1);
				}
			}
			// i = man, j = woman
			if (i >= W) {
				for (j = 0; j < W; j++) {
					if (!loop(cur, j, cur->y, true)) {
						queueE(cur, j, cur->y, cur->size + 1);
					}
				}
			}
		}
	}
	cout << minCost << endl;
}

int main() {
	int T, i, j;
#if BENCH
	freopen("1_emergency.txt","r",stdin);
#endif
	ios_base::sync_with_stdio(false);
	cin >> T;
	for (int tc = 0; tc < T; tc++) {
		cin >> W >> M;
		for (i = 0; i < M + W; i++) {
			int guy;
			cin >> guy;
			h[guy-1] = i;
		}
		for (i = 0; i < W; i++) {
			CLRN(w[i], M);
			for (j = 0; j < M; j++)
				cin >> w[i][j];
		}
		cout << "Case #" << tc + 1 << endl;
#if 1
		solve();
#else
		if (W + M <= 100)
			solveBrute();
		else
			cout << "-911" << endl;
#endif
	}
	return 0;
}
