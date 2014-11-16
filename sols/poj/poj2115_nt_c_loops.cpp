/*
 * POJ 2115 C Loops
 * Number theory, GCD, extended euclidean algorithm
 */
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
#define DBG 0 // modify this for enabling/disable debug
#else
#define DBG 0
#endif // BENCH

#define D(...) do { if (DBG) fprintf(stderr, __VA_ARGS__); } while (0)

#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, (n)*sizeof x[0]);
#define CLRVN(x, v, n) memset(x, v, (n)*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
	typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

typedef long long Num;

Num a,b,c,k;

Num gcd(Num a, Num b)
{
  Num c;
  while (a != 0) {
     c = a; a = b % a; b = c;
  }
  return b;
}

void exgcd(Num a, Num b, Num c, Num &x, Num &y) {
    if (!b) {
        x = c / a, y = 0;
        return;
    }
    Num tx, ty;
    exgcd(b, a % b, c, tx, ty);
    x = ty, y = tx - a / b * ty;
}

void solve() {
	// Solve diophantine eq. Cx + y 2^k == B - A
	Num m = 1LL << k;
	Num g = gcd(c, m);
	D("gcd(%lld, %lld) = %lld\n", c, 1 << k, g);

	if ((b - a) % g == 0) {
		Num x, y;
		exgcd(c, m, b - a, x, y);
		m /= g;
		cout << (x % m + m) % m << endl;
	} else
		cout << "FOREVER" << endl;
}

int main() {
#if BENCH
	freopen("files/poj2115_nt_c_loops.txt","r",stdin);
#endif
	while (~scanf("%lld%lld%lld%lld", &a, &b, &c, &k) && (a||b||c||k)) {
		solve();
	}
	return 0;
}
