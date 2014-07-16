/* poj 1177 Picture */
/* segment tree, line sweep, discretize, deferred */

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
#endif // BENCH

#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, (n)*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
	typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

typedef int Num;
const Num maxn = 5000;

int n;
int len;	// new length
int curX;

struct Line {
	int x, y1, y2;
	int dir;
	Line(int x = 0, int y1 = 0, int y2 = 0, int dir = 0) :
		x(x), y1(y1), y2(y2), dir(dir) { }
	bool operator<(const Line &r) const {
	    /* left to right, open first */
		return x < r.x || (x == r.x && dir > r.dir);
	}
} seg[maxn*2];

/* Segment tree */
#define L(u) u<<1
#define R(u) u<<1|1
#define lson u<<1, b, mid
#define rson u<<1|1, mid, e
#define defmid int mid = (b + e) >> 1
const int root = 1;

template<int MAX, int VALS, typename Num>
struct SegTree {
	struct SegNode {
		int cover;	/* the value of the interval, -1 if not fully covered */
		bool coverL, coverR;
	};
	SegNode tree[MAX];
	Num Y[VALS];
	int iY; // next index of Y
	int nY; // total count of Y

	void init(int u, int b, int e) {
		tree[u].cover = 0;
	    if (b + 1 == e)
	        return;
	    defmid;
	    init(lson);
	    init(rson);
	}

	void clearY() {
		iY = 0;
	}

	void pushY(Num v) {
		Y[iY++] = v;
	}

	/* returns nY - 1 */
	int discreteInit() {
	    sort(Y, Y + iY);
		nY = unique(Y, Y + iY) - Y - 1;
		init(root, 0, nY);
		return nY;
	}

	void pushdown(int u, int b, int e) {
		if (tree[u].cover != -1) {
			tree[L(u)].cover = tree[u].cover;
			tree[R(u)].cover = tree[u].cover;
		}
	}

	void pushup(int u, int b, int e) {
		if (tree[L(u)].cover != tree[R(u)].cover)
			tree[u].cover = -1;
		else
			tree[u].cover = tree[L(u)].cover;
	}

	void update(int u, int b, int e, Num l, Num r, int val) {
	    if (tree[u].cover != -1 && l == Y[b] && Y[e] == r) {
	    	// draw line
	    	if (tree[u].cover == 0 && val == 1 || tree[u].cover == 1 && val == -1)
	    		len += Y[e] - Y[b];

	    	tree[u].cover += val;
	        return;
	    }

	    pushdown(u, b, e);

	    defmid;
	    if (r <= Y[mid])
	        update(lson, l, r, val);
	    else if (l >= Y[mid])
	        update(rson, l, r, val);
	    else {
	        update(lson, l, Y[mid], val);
	        update(rson, Y[mid], r, val);
	    }

	    pushup(u, b, e);
	}

	// returns uncovered end points
	int query(int u, int b, int e) {
		if (b + 1 == e) {
		    tree[u].coverL = tree[u].coverR = tree[u].cover > 0;
			return 0;
		}

		pushdown(u, b, e);

		defmid;
		int vis = query(lson) + query(rson);

		if (tree[L(u)].coverR != tree[R(u)].coverL)
			vis += 1;

		// pushup
		tree[u].coverL = tree[L(u)].coverL;
		tree[u].coverR = tree[R(u)].coverR;

		return vis;
	}
};

SegTree<maxn*2*3,maxn*2+2,Num> st;

int main() {
#if BENCH
	freopen("files/poj1177_picture.txt","r",stdin);
#endif
	while (~scanf("%d", &n)) {
		int peri = 0;
		st.clearY();
		st.pushY(numeric_limits<Num>::min());
		REP(i,n) {
			int x1, y1, x2, y2;
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			seg[2*i] = Line(x1, y1, y2, 1);
			seg[2*i+1] = Line(x2, y1, y2, -1);
			st.pushY(y1);
			st.pushY(y2);
		}
		st.pushY(numeric_limits<Num>::max());

		int nY = st.discreteInit();
		sort(seg, seg + 2*n);

		int lastX = 0, lastVis = 0;
		REP(i,2*n) {
			len = 0;
			curX = seg[i].x;
			st.update(root, 0, nY, seg[i].y1, seg[i].y2, seg[i].dir);
			peri += len;
			if (i < 2*n - 1 && seg[i].x == seg[i+1].x)
			    continue;
			int vis = st.query(root, 0, nY);
			peri += lastVis * (seg[i].x - lastX);
			lastX = seg[i].x;
			lastVis = vis;
		}
		printf("%d\n", peri);
	}
	return 0;
}
