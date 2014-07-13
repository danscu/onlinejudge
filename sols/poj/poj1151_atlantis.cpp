/* segment tree, discrete, line sweep (left to right) */
/* poj 1151, C++ AC, G++ WA */

#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>
#include <limits>
#include <climits>
#include <cfloat>
#include <cmath>
#include <map>
#include <list>
#include <fstream>

using namespace std;

const int maxn = 101 * 2;
const int MAXTREE = maxn * 3;
typedef double Num;

// Segment tree stuff
#define lson u<<1
#define rson u<<1|1
#define defmid int mid = (b + e) >> 1
const int root=1;
struct Seg {
	double x, y1, y2;
	int dir; // 1 = in, -1 = out
	Seg(double x=0, double y1=0, double y2=0, int d=0) :
		x(x), y1(y1), y2(y2), dir(d) {}
	bool operator < (const Seg &a) const { return x < a.x; }
};
Seg seg[maxn];

// indexed value
Num Y[maxn];

int cover[MAXTREE];
double len[MAXTREE];

void stree_init(int u, int b, int e) {
	len[u] = 0, cover[u] = 0;
	if (b == e)
		return;
	defmid;
	stree_init(lson, b, mid);
	stree_init(rson, mid+1, e);
}

void stree_pushup(int u, int b, int e) {
	if (cover[u])
		len[u] = Y[e+1] - Y[b];
	else if (b == e)
		len[u] = 0;
	else
		len[u] = len[lson] + len[rson];
}

void stree_update(int u, int b, int e, int i, int j, int dir) {
	if (i <= b && e <= j) { // complete cover
		cover[u] += dir;
		stree_pushup(u, b, e);
		return;
	}

	defmid;

	if (j <= mid)
		stree_update(lson, b, mid, i, j, dir);
	else if (i > mid)
		stree_update(rson, mid + 1, e, i, j, dir);
	else {
		stree_update(lson, b, mid, i, mid, dir);
		stree_update(rson, mid + 1, e, mid+1, j, dir);
	}
	stree_pushup(u, b, e);
}

int bfind(double val, int n) {
	int b = 1, e = n;
	while (b <= e) {
		defmid;
		if (Y[mid] == val) return mid;
		else if (Y[mid] < val) b = mid + 1;
		else e = mid - 1;
	}
}

int main() {
#if BENCH
	freopen("files/poj1151_atlantis.txt", "r", stdin);
#endif
	int i;
	int n;
	int tc = 0;
	while (scanf("%d", &n), n) {
		int cv = 0;
		for (i = 0; i < n; i ++) {
			double x1,x2,y1,y2;
			scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
			seg[++cv] = Seg(x1,y1,y2,1), Y[cv] = y1;
			seg[++cv] = Seg(x2,y1,y2,-1), Y[cv] = y2;
		}

		sort(seg+1, seg+1+cv); sort(Y+1, Y+1+cv);
		int uv = 1;
		for (i = 2; i <= cv; i++)
			if (Y[i] != Y[i-1])
				Y[++uv] = Y[i];

		stree_init(root, 1, uv);

		double sum = 0;

		for (i = 1; i < cv; i++) {
			int l = bfind(seg[i].y1, uv);
			int r = bfind(seg[i].y2, uv) - 1;
			stree_update(root, 1, uv, l, r, seg[i].dir);
			sum += len[root] * (seg[i+1].x - seg[i].x);
		}
		printf("Test case #%d\n", ++tc);
		printf("Total explored area: %.2lf\n\n", sum);
	}
	return 0;
}
