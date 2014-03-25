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

# define DBG 1
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

Num A, B, K;
char lastOp;
int opCnt;

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

#if DBG
Num da, db;
#endif

void execute(char op, int cnt) {
	cout << op << " " << cnt << endl;
#if DBG
	for (int i = 0; i < cnt; i++) {
		switch (op) {
		case OPX:
			da = da + db;
			break;
		case OPY:
			da = da - db;
			break;
		case OPZ:
			db = da - db;
			break;
		}
	}
#endif
}

void addOp(char op, int cnt = 1) {
	if (op != lastOp) {
		if (lastOp != OP0)
			execute(lastOp, opCnt);
		opCnt = cnt;
		lastOp = op;
	} else
		opCnt+=cnt;
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
		cout << "YES" << endl;
		int a = A, b = B;
#if DBG
		da = A, db = B;
#endif
		lastOp = OP0; opCnt = 0;
		while (a != b) {
			if (a < b) {
				addOp(OPX);
				addOp(OPZ);
				addOp(OPY);
				swap(a, b);
			}
			addOp(OPY);
			a = a - b;
		}
		D( cout << "gcd " << a << endl; )
		int z = K / a;
		if (z < 0)
			addOp(OPY, - z + 1);
		else
			addOp(OPX, z - 1);

		if (lastOp != OP0)
			addOp(-1); // flush

		D( cout << "da = " << da << " db = " << db << endl; )

		return;
	}
	cout << "NO" << endl;
}

void gen() {
	Num R = 10000;
	Num d = rand() % R; // gcd
	Num u = rand() % R; // a/gcd
	Num v = rand() % R; // b/gcd
	Num w = rand() % R; // K/gcd
	A = d * u;
	B = d * v;

	Num n,m;
	Num gc = gcd(A, B, &n, &m);
	K = gc * w;
	D (cout << "A=" << A << " B=" << B << " K=" << K << endl;)
}

int main() {
	int T;
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
