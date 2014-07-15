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

#define VERIFY

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
const Num maxn = 100006;
Num n,k;
Num xmax, xmin, ymax, ymin;

struct Pt {
	Num x, y;
	Pt(Num x=0, Num y=0) : x(x), y(y) { }
};

struct SortX {
	bool operator()(const Pt &a, const Pt &b) const {
		return a.x < b.x || (a.x == b.x && a.y < b.y);
	}
} sortX;

struct SortY {
	bool operator()(const Pt &a, const Pt &b) const {
		return a.y < b.y || (a.y == b.y && a.x < b.x);
	}
} sortY;

Pt pby[maxn];
Pt pbx[maxn];

int ix[maxn]; int nx;
int iy[maxn]; int ny;

// bfs search
const int MAX_NODES = 10000000;
struct Node {
	int top, bottom, left, right; /* all inclusive */
	int removed; /* dots in the rectangle */
	int len;  /* bounding square size */
	void updateLen() {
		len = max(
		        pby[iy[bottom]].y - pby[iy[top]].y,
		        pbx[ix[right]].x - pbx[ix[left]].x
		        );
	}
};

struct Buffer {
private:
	int n;
	Node nodes[MAX_NODES];
	Node *head, *tail;
public:
	Buffer() {
		clear();
	}
	Node *alloc() {
		if (n == MAX_NODES)
			return NULL;
		n++;
		Node *ret = tail;
		if (++tail > &nodes[MAX_NODES])
			tail = &nodes[0];
		return ret;
	}
	Node *read() {
		if (n == 0)
			return NULL;
		n--;
		Node *ret = head;
		if (++head > &nodes[MAX_NODES])
			head = &nodes[0];
		return ret;
	}
	void clear() {
		head = tail = &nodes[0];
		n = 0;
	}
	int size() { return n; }
} buf;

struct NodeSort {
	bool operator()(const Node *a, const Node *b) {
		return a->removed < b->removed ||
				(a->removed == b->removed && a->len < b->len);
	}
};

typedef set<Node*,NodeSort> Que;
Que que;

Num getnum() {
	char cc,s;
	int dd;
	while (cc = getchar(), (cc<'0'||cc>'9')&&cc!='-');
	s=cc=='-'?-1:1;
	dd=cc=='-'?0:cc-'0';
	while (cc = getchar(), cc>='0'&&cc<='9')
		dd = dd*10+cc-'0';
	return dd*s;
}

void index() {
	nx = 0; ix[0] = 0;
	FOR(i,1,n-1)
		if (pbx[i].x != pbx[ix[nx]].x)
			ix[++nx] = i;

	ny = 0; iy[0] = 0;
	FOR(j,1,n-1)
		if (pby[j].y != pby[iy[ny]].y)
			iy[++ny] = j;
}

Num searchDotsH(const Node *node, int y, int &first, int &last) {
	first = -1, last = -1;
	int low, hi, m;

	// find first
	low = iy[y], hi = (y == ny) ? (n - 1) : (iy[y+1] - 1);

	while (low <= hi) {
		m = (low + hi) / 2;
		if (pby[m].x >= pbx[ix[node->left]].x) {
			if (low >= hi - 1) {
				first = m;
				break;
			}
			hi = m;
		} else
			low = m + 1;
	}

	if (first < 0)
		return 0;

	// find last
	low = iy[y], hi = (y == ny) ? (n - 1) : (iy[y+1] - 1);

	while (low <= hi) {
		m = (low + hi + 1) / 2;
		if (pby[m].x <= pbx[ix[node->right]].x) {
			if (low >= hi - 1) {
				last = m;
				break;
			}
			low = m;
		} else
			hi = m - 1;
	}

	if (last < 0)
		return 0;

	return last - first + 1;
}

Num searchDotsV(const Node *node, int x, int &first, int &last) {
	first = -1, last = -1;
	int low, hi, m;

	// find first
	low = ix[x], hi = (x == nx) ? (n - 1) : (ix[x+1] - 1);

	while (low <= hi) {
		m = (low + hi) / 2;
		if (pbx[m].y >= pby[iy[node->top]].y) {
			if (low >= hi - 1) {
				first = m;
				break;
			}
			hi = m;
		} else
			low = m + 1;
	}

	if (first < 0)
		return 0;

	// find last
	low = ix[x], hi = (x == nx) ? (n - 1) : (ix[x+1] - 1);

	while (low <= hi) {
		m = (low + hi + 1) / 2;
		if (pbx[m].y <= pby[iy[node->bottom]].y) {
			if (low >= hi - 1) {
				last = m;
				break;
			}
			low = m;
		} else
			hi = m - 1;
	}

	if (last < 0)
		return 0;

	return last - first + 1;
}

void trim(Node *cur) {
    int first, last;
    int newTop = cur->top;
    int newBound = 0;
    while (newBound == 0 && newTop <= cur->bottom) {
        newBound = searchDotsH(cur, newTop, first, last);
        newTop++;
    }
    cur->top = newTop-1;

    // bottom-
    int newBot = cur->bottom;
    newBound = 0;
    while (newBound == 0 && newBot >= cur->top) {
            newBound = searchDotsH(cur, newBot, first, last);
        --newBot;
    }
    cur->bottom = newBot+1;

    // left+
    int newLeft = cur->left;
    newBound = 0;
    while (newBound == 0 && newLeft <= cur->right) {
            newBound = searchDotsV(cur, newLeft, first, last);
            ++newLeft;
    }
    cur->left = newLeft-1;

    // right-
    int newRight = cur->right;
    newBound = 0;
    while (newBound == 0 && newRight >= cur->left) {
        newBound = searchDotsV(cur, newRight, first, last);
        --newRight;
    }
    cur->right = newRight+1;
}

inline bool addNewNode(int top, int bottom, int left, int right, int removed) {
	static Node *el = 0;
	if (el == 0) {
		el = buf.alloc();
		if (!el)
			return false;
	}

	el->top = top;
	el->bottom = bottom;
	el->left = left;
	el->right = right;
	el->removed = removed;
	trim(el);
	el->updateLen();

	pair<Que::iterator,bool> ret = que.insert(el);
	if (ret.second)
		el = 0;

	return true;
}

// length of the square
Num solve() {
	sort(pbx, pbx+n, sortX);
	sort(pby, pby+n, sortY);
	index();

	// init
	que.clear();
	buf.clear();

	// bfs
	addNewNode(0, ny, 0, nx, 0);

	int bestLen = numeric_limits<Num>::max();
	Node *cur;
	while (!que.empty()) {
		Que::iterator it = que.begin();
		cur = *it; que.erase(it);

		// check done
		if (cur->removed > k)
			break;

		// check best solution
		if (cur->removed <= k && bestLen > cur->len)
			bestLen = cur->len;

		// expand node: four directions, and get the number of dots
		// top+
		int first, last;
		int newTop = cur->top;
		int removedDots = 0;
		while (removedDots==0 && newTop <= cur->bottom) {
		    removedDots = searchDotsH(cur, newTop, first, last);
			newTop++;
		}
		if (!addNewNode(newTop, cur->bottom, cur->left, cur->right,
				cur->removed + removedDots))
			break;

		// bottom-
		int newBot = cur->bottom;
		removedDots = 0;
		while ((removedDots==0) && newBot >= cur->top) {
				removedDots = searchDotsH(cur, newBot, first, last);
			--newBot;
		}
		if (!addNewNode(cur->top, newBot, cur->left, cur->right,
				cur->removed + removedDots))
			break;

		// left+
		int newLeft = cur->left;
		removedDots = 0;
		while ((removedDots==0) && newLeft <= cur->right) {
			removedDots = searchDotsV(cur, newLeft, first, last);
			++newLeft;
		}
		if (!addNewNode(cur->top, cur->bottom, newLeft, cur->right,
				cur->removed + removedDots))
			break;

		// right-
		int newRight = cur->right;
		removedDots = 0;
		while ((removedDots==0) && newRight >= cur->left) {
		    removedDots = searchDotsV(cur, newRight, first, last);
		    --newRight;
		}
		if (!addNewNode(cur->top, cur->bottom, cur->left, newRight,
				cur->removed + removedDots))
			break;
	}

    return bestLen;
}

Num solveBrute() {
	sort(pbx, pbx+n, sortX);
	sort(pby, pby+n, sortY);
	index();

	// binary search
	int low = 0, len = low, hi = max(xmax - xmin, ymax - ymin);
	bool possible = false;
	while (low <= hi) {
		len = (low + hi) / 2;
		possible = false;

		int i,j,is,js;
		Num dots;
		Num maxDots = 0;

		/* search len x len squares */
		for (is = 0; is <= nx && !possible; is++)
			for (js = 0; js <= ny && !possible; js++) {
				dots = 0;
				for (i = is; i <= nx; i++) {
					// i scans in the square along x
					if (pbx[ix[i]].x > pbx[ix[is]].x + len)
						break;
					// j scans in the square along y
					for (j = ix[i]; j < n && pbx[j].x == pbx[ix[i]].x; j++) {
						if (pbx[j].y >= pby[iy[js]].y) {
							if (pbx[j].y > pby[iy[js]].y + len)
								break;
							dots++;
						}
					}
				}
				// process square
				maxDots = max(maxDots, dots);
				if (maxDots >= n - k)
					possible = true;
			}

		// search done
		if (possible) {
			if (low >= hi - 1)
				break;
			else
				hi = len;
		}
		else
			low = len + 1;
	}

	if (possible)
		return len;

	return -1; // impossible
}

int main() {
	int T;
	Num i, j;
#if BENCH
	freopen("files/pts.in","r",stdin);
#endif

	T = getnum();
	for (int tc = 0; tc < T; tc++) {
		n = getnum(); k = getnum();
		xmin = ymin = numeric_limits<Num>::max();
		xmax = ymax = numeric_limits<Num>::min();

		for (i = 0; i < n; i++) {
		    Num x,y;
			x = getnum(); y = getnum();
			pbx[i].x = pby[i].x = x; pbx[i].y = pby[i].y = y;
			xmin = min(xmin, x);
			xmax = max(xmax, x);
			ymin = min(ymin, y);
			ymax = max(ymax, y);
		}

		printf("Case #%d\n", tc + 1);
#ifdef VERIFY
		int ans1, ans2;
		printf("ans=%d", ans1 = solveBrute());
		printf(" my=%d\n", ans2 = solve());
		if (ans1 != ans2) {
			cout << "ERROR" << endl;
			exit(-1);
		}
#else
		if (k > 2000)
		    printf("0\n");
		else
		    printf("%d\n", solve());
#endif
	}
	return 0;
}
