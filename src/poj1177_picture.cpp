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
const Num INF = numeric_limits<Num>::max();

int n;
int len;	// new length
int top, bottom;

struct Line {
	int x, y1, y2;
	int dir;
	Line(int x = 0, int y1 = 0, int y2 = 0, int dir = 0) :
		x(x), y1(y1), y2(y2), dir(dir) { }
	bool operator<(const Line &r) const {
		return x < r.x;
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
		int add;	/* used for delayed update */
		int hors;	/* number of visible horizontal lines in the interval */
	};
	SegNode tree[MAX];
	Num Y[VALS];
	int iY; // next index of Y
	int nY; // total count of Y

	void init(int u, int b, int e) {
		tree[u].cover = tree[u].add = tree[u].hors = 0;
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

	void sortY() {
		sort(Y, Y + iY);
	}

	int uniqY() {
		return unique(Y, Y + iY) - Y;
	}

	/* returns nY - 1 */
	int discreteInit() {
		sortY();
		nY = uniqY() - 1;
		init(root, 0, nY);
		return nY;
	}

	void pushdown(int u, int b, int e) {
		if (tree[u].cover != -1) {
			tree[L(u)].cover = tree[u].cover + tree[u].add;
			tree[R(u)].cover = tree[u].cover + tree[u].add;
		}
		if (tree[u].add) {
			tree[L(u)].add += tree[u].add;
			tree[R(u)].add += tree[u].add;
			tree[u].add = 0;
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

	    	// add deferred value
	    	tree[u].add += val;
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

	// add endpoint
	void updateE(int u, int b, int e, Num l, int val) {
		if (b + 1 == e) {
			tree[u].hors += val;
			return;
		}

		defmid;
		if (l < Y[mid])
			updateE(lson, l, val);
		else
			updateE(rson, l, val);

		// push up
		tree[u].hors = tree[L(u)].hors + tree[R(u)].hors;
	}

	// returns uncovered end points
	int queryE(int u, int b, int e) {
		if (b + 1 == e)
			return 0;

		pushdown(u, b, e);

		defmid;
		int vis = queryE(lson) + queryE(rson);

		if ((tree[L(u)].cover > 0) != (tree[R(u)].cover > 0))
			vis += 1;

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

		int lastX;
		REP(i,2*n) {
			len = 0;
			top = seg[i].y1;
			bottom = seg[i].y2;
			st.update(root, 0, nY, seg[i].y1, seg[i].y2, seg[i].dir);
			peri += len;

			st.updateE(root, 0, nY, seg[i].y1, seg[i].dir);
			st.updateE(root, 0, nY, seg[i].y2, seg[i].dir);
			int vis = st.queryE(root, 0, nY);
			peri += vis * (i ? seg[i].x - lastX : 0);
			lastX = seg[i].x;
		}
		printf("%d\n", peri);
	}
	return 0;
}

/* TODO
 * Add variables coverL and coverR, update them in pushup()
 * Compare difference to find edges
 */
 */
