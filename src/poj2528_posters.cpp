/* segment tree rmq */

#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>
#include <climits>
#include <cfloat>
#include <cmath>
#include <map>
#include <list>
#include <fstream>

using namespace std;

const int maxn = 10004;
const int MAXIND = maxn * 4;

typedef int Num;

struct Interval {
	int begin;
	int end;
	bool vis;
	int ib;
	int ie;
};

struct Event {
	int x;
	int interval;
	bool isBegin;
	bool operator<(const Event &e) const {
		return x < e.x;
	}
};

Interval v[maxn];
Event ev[maxn*2];
int evi[maxn*2];	// get event index from x
int stree[MAXIND];	// stores interval id
int ntree;

void __stree_init(int node, int b, int e) {
	if (b == e) {
		stree[node] = ev[evi[b]].interval;
	} else {
		// compute the values in the left and right subtrees
		__stree_init(2 * node, b, (b + e) / 2);
		__stree_init(2 * node + 1, (b + e) / 2 + 1, e);
		// search for the minimum value in the first and second half of the interval
		if (stree[2 * node] >= stree[2 * node + 1])
			stree[node] = stree[2 * node];
		else
			stree[node] = stree[2 * node + 1];
	}
}

Num  __stree_query(int node, int b, int e, int i, int j) {
	Num p1, p2;

	// if the current interval doesn't intersect, the query interval, return -1
	if (i > e || j < b)
		return -1;

	// if the current interval is included in the query interval, return stree[node]
	if (b >= i && e <= j)
		return stree[node];

	// compute the minimum position in the left and right part of the interval
	p1 = __stree_query(2*node, b, (b+e)/2, i, j);
	p2 = __stree_query(2*node+1, (b+e)/2+1, e, i, j);

	// return the position where the overall minimum is
	if (p1 == -1)
		return p2;
	if (p2 == -1)
		return p1;
	return max(p1, p2);
}

Num  __stree_update(int node, int b, int e, int i, int j, int val) {
	Num p1, p2;

	// if the current interval doesn't intersect, the query interval, return -1
	if (i > e || j < b)
		return -1;

	// if the current interval is included in the query interval, return stree[node]
	if (b >= i && e <= j)
		return stree[node];

	// compute the minimum position in the left and right part of the interval
	p1 = __stree_query(2*node, b, (b+e)/2, i, j);
	p2 = __stree_query(2*node+1, (b+e)/2+1, e, i, j);

	// return the position where the overall minimum is
	if (p1 == -1)
		return p2;
	if (p2 == -1)
		return p1;
	return max(p1, p2);
}

int main() {
	// input
#if BENCH
	freopen("files/poj2528_posters.in", "r", stdin);
#endif
	int i, nu;
	int c, n;
	scanf("%d",&c);
	for (int tc=0;tc<c;tc++) {
		scanf("%d",&n);
		int ie = 0;
		for (i = 0; i < n; i ++) {
			scanf("%d%d",&v[i].begin, &v[i].end);
			v[i].vis = false;
			ev[ie].interval = i;
			ev[ie].isBegin = true;
			ev[ie].x = v[i].begin; ie++;
			ev[ie].interval = i;
			ev[ie].isBegin = false;
			ev[ie].x = v[i].end; ie++;
		}

		sort(ev, ev+2*n);
		// index x (nu = max index of unique x values)
		for (i = 0, nu = -1; i < 2*n; i++) {
			if (nu == -1 || ev[nu].x != ev[i].x) {
				nu++;
				evi[nu] = i;
			}
			if (ev[i].isBegin)
				v[ev[i].interval].ib = nu;
			else
				v[ev[i].interval].ie = nu;
			if (ev[i].interval > ev[evi[nu]].interval)
				evi[nu] = i;
		}

		for (ntree = 1; ntree <= nu; ntree *= 2)
			;
		ntree--;
		__stree_init(1, 0, ntree);

		// process
		for (i = 0; i < 2*n; i++)
			if (ev[i].isBegin)
				__stree_update(1, 0, ntree,
						v[ev[i].interval].ib, v[ev[i].interval].ie, ev[i].interval);
	}
	return 0;
}
