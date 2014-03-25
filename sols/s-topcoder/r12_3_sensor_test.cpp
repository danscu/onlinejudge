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
#define CLRN(x, n) memset(x, 0, n*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#endif // BENCH

#define OP0 0
#define OPX 'X'
#define OPY 'Y'
#define OPZ 'Z'

typedef long long Num;
const int maxn = 1010;
struct Coef {
	Num ax, ay; // var a
	Num bx, by; // var b
	Coef *parent;
	int lines;
	int cnt;
	char op;
	Coef() { }
	Coef(Num ax, Num ay, Num bx, Num by, char op, Coef *parent, int lines) :
		ax(ax), ay(ay), bx(bx), by(by), op(op), parent(parent), lines(lines) { }
};

Num A, B, K;
#define QSIZE (maxn*maxn)
Coef que[QSIZE];
int qh, qr;

// visited dict
struct Dict {
	typedef map<Num,Dict*> DMap;
	DMap c;
} dict;

Coef &readQueue() {
	Coef &r(que[qr++]);

	if (qr == QSIZE)
		qr = 0;

	return r;
}

Coef &getNew() {
	Coef &r(que[qh++]);

	if (qh == QSIZE)
		qh = 0;

	// full
	if (qh == qr) {
		cout << "OUT OF MEMORY" << endl;
		exit(0);
	}

	return r;
}

void rewindQueue() {
	qh--;
	if (qh < 0)
		qh = QSIZE - 1;
}

Dict *_addToDict(Num x, Dict *u, bool leaf) {
	Dict::DMap::iterator it = u->c.find(x);
	Dict *next = 0;
	if (it == u->c.end()) {
		if (!leaf)
			next = new Dict();
		u->c[x] = next;
	} else
		next = it->second;
	return next;
}

Dict *_inDict(Num x, Dict *u, bool leaf) {
	Dict::DMap::iterator it = u->c.find(x);
	if (it == u->c.end())
		return NULL;
	else
		return leaf ? (Dict*)1 : it->second;
}

bool inDict(Coef &e) {
	Dict *u = &dict;
	u = _inDict(e.ax, u, false);
	if (!u) return false;
	u = _inDict(e.ay, u, false);
	if (!u) return false;
	u = _inDict(e.bx, u, false);
	if (!u) return false;
	u = _inDict(e.by, u, true);
	return u;
}

void tryAddToDict(Coef &e) {
	if (inDict(e)) {
		rewindQueue();
	}

	Dict *u = &dict;
	u = _addToDict(e.ax, u, false);
	u = _addToDict(e.ay, u, false);
	u = _addToDict(e.bx, u, false);
	_addToDict(e.by, u, true);
}

void clearDict(Dict *u) {
}

Num gcd(Num a, Num b, Num *ss, Num *tt) {
	Num s = 0, old_s = 1;
	Num t = 1, old_t = 0;
	Num r = b, old_r = a;
	Num tmp;
	while (r != 0) {
		Num q = old_r / r;
		tmp = r; r = old_r - q * r; old_r = tmp;
		tmp = s; s = old_s - q * s; old_s = tmp;
		tmp = t; t = old_t - q * t; old_t = tmp;
	}
	*ss = old_s; *tt = old_t;
	return old_r;
}

void printLines(Coef *u, char lastOp) {
	if (u->parent != &que[0])
		printLines(u->parent, u->op);
	if (u->op != lastOp)
		cout << u->op << " " << u->cnt << endl;
}

void solve() {
	Num n, m;
	Num d = gcd(A, B, &n, &m);
	bool sol = K % d == 0;
	if (sol) {
		Num x0 = n * K / d, y0 = m * K / d;
		D( cout << "gcd = " << d << endl; )
		D( cout << "n = " << n << " m = " << m << endl; )
		D( cout << "x0 = " << x0 << " y0 = " << y0 << endl; )

		// bfs search
		que[0] = Coef(1, 0, 0, 1, OP0, NULL, 0);
		qh = 1; qr = 0;
		while (qr != qh) {
			Coef &cur = readQueue();

			// TEST *****************************
			//if (cur.lines > 1000)
				//break;

			// sol?
			if (cur.ax * A + cur.ay * B == K) {
				printLines(&cur, -1);
				return;
			}

			Coef &next = getNew();

			if (cur.op != OPZ) {
				// Z
				next.op = OPZ;
				next.ax = cur.ax;
				next.ay = cur.ay;
				next.bx = cur.ax - cur.bx;
				next.by = cur.ay - cur.by;
				next.parent = &cur;
				next.lines = cur.lines + 1;
				next.cnt = 1;
				tryAddToDict(next);
			}

			if (cur.op != OPY) {
				// X
				Coef &next = getNew();
				next.op = OPX;
				next.ax = cur.ax + cur.bx;
				next.ay = cur.ay + cur.by;
				next.bx = cur.bx;
				next.by = cur.by;
				next.parent = &cur;
				next.lines = cur.op == OPX ? cur.lines : cur.lines + 1;
				next.cnt = cur.op == OPX ? cur.cnt + 1 : 1;
				tryAddToDict(next);
			}

			if (cur.op != OPX) {
				// Y
				Coef &next = getNew();
				next.op = OPY;
				next.ax = cur.ax - cur.bx;
				next.ay = cur.ay - cur.by;
				next.bx = cur.bx;
				next.by = cur.by;
				next.parent = &cur;
				next.lines = cur.op == OPY ? cur.lines : cur.lines + 1;
				next.cnt = cur.op == OPY ? cur.cnt + 1 : 1;
				tryAddToDict(next);
			}
		}
	}
	cout << "NO" << endl;
}

void gen() {
	Num R = 4000;
	Num d = rand() % R; // gcd
	Num u = rand() % R; // a/gcd
	Num v = rand() % R; // b/gcd
	Num w = rand() % R; // K/gcd
	A = d * u;
	B = d * v;

	Num n,m;
	Num gc = gcd(A, B, &n, &m);
	K = gc * w;
}

int main() {
	int T;
#if BENCH
	freopen("3_sensor.txt","r",stdin);
#endif
	srand(time(NULL));
	ios_base::sync_with_stdio(false);
	T = 1;
	for (int tc = 0; tc < T; tc++) {
		gen();
		cout << "Case #" << tc + 1 << endl;
		solve();
	}
	return 0;
}
