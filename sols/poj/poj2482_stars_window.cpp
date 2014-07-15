/* 1d segment tree + discrete + sweep line */
/* poj 2482 */

/**
 * Solution note:
 *
 * 1) Main idea is to treat each star as a rectangle, and the target window as a point.
 *    the rectangle is represented as
 *    (x, y + h - 1) ---------------------------- (x + w - 1, y + h - 1)
 *          |                                                |
 *          |                                                |
 *       (x, y) ---------------------------------------(x + w - 1, y)
 *
 *    The segment tree contains vertical line segments as elements. The entering vertical
 *    line [y, y + h - 1] is marked with value c, and the exiting vertical line [y, y + h - 1]
 *    is marked with value -c.
 *
 *    The segments are sorted by the x value.
 *
 * 2) The segments are updated into the segment tree in the sorted order. The update() function
 *    will update the brightness value for each interval. Delayed values are pushed down and
 *    the result is pushed up when recursion is done.
 *
 * 3) After inserting each line segment, the total
 */

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

#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, (n)*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
    typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

const int maxn = 20005;
const int MAXTREE = 2 * maxn * 3;
typedef long long Num;

// Segment tree stuff
#define L(u) u<<1
#define R(u) u<<1|1
#define lson u<<1, b, mid
#define rson u<<1|1, mid+1, e
#define defmid int mid = (b + e) >> 1

const int root=1;

struct Line {
    Num x, y1, y2;
    int val;
    bool operator<(const Line &b) const {
        return x < b.x || (x == b.x && val > b.val);
    }
} seg[maxn*2];

struct SegNode {
    Num sum; // sum = max brightness in all rectangles
    int add; // used for delayed update
};

SegNode tree[MAXTREE];

Num Y[maxn*2];

void stree_init(int u, int b, int e) {
    tree[u].sum = tree[u].add = 0;
    if (b == e)
        return;
    defmid;
    stree_init(lson);
    stree_init(rson);
}

void stree_pushdown(int u, int b, int e) {
    tree[L(u)].sum += tree[u].add;
    tree[L(u)].add += tree[u].add;
    tree[R(u)].sum += tree[u].add;
    tree[R(u)].add += tree[u].add;
    tree[u].add = 0;
}

void stree_pushup(int u, int b, int e) {
    tree[u].sum = max(tree[L(u)].sum, tree[R(u)].sum);
}

void stree_update(int u, int b, int e, Num l, Num r, int val) {
    if (l == Y[b] && Y[e] == r) {
        tree[u].sum += val;
        tree[u].add += val;
        return;
    }

    if (b == e)
        return;

    if (tree[u].add)
        stree_pushdown(u, b, e);

    defmid;
    if (r <= Y[mid])
        stree_update(lson, l, r, val);
    else if (l >= Y[mid+1])
        stree_update(rson, l, r, val);
    else {
        stree_update(lson, l, Y[mid], val);
        stree_update(rson, Y[mid+1], r, val);
    }

    stree_pushup(u, b, e);
}

int main() {
#if BENCH
	freopen("files/poj2482_stars_window.txt", "r", stdin);
#endif

	int n, w, h;
	while (~scanf("%d%d%d", &n, &w, &h)) {
	    REP(i,n) {
	        scanf("%lld%lld%lld", &seg[i].x, &seg[i].y1, &seg[i].val);
	        Y[i*2+1] = seg[i].y1;
	        seg[i].y2 = Y[i*2+2] = seg[i].y1 + h - 1;
	        seg[i+n] = seg[i];
	        seg[i+n].x = seg[i].x + w - 1;
	        seg[i+n].val = -seg[i].val;
        }
	    sort(Y+1, Y+2*n+1);
	    sort(seg, seg + 2*n);

	    int cnt = unique(Y+1, Y + 2*n + 1) - Y - 1; // discretization

	    stree_init(root, 1, cnt);
	    Num ans = 0;
	    REP(i,2*n) {
	        stree_update(root, 1, cnt, seg[i].y1, seg[i].y2, seg[i].val);
	        ans = max(ans, tree[root].sum);
	    }
	    printf("%lld\n", ans);
	}
	return 0;
}
