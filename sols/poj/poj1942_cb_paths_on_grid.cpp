/*
 * POJ 1942
 * Paths on grid
 * Combinatorics
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
#define DBG 1 // modify this for enabling/disable debug
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

Num n, m;

Num binom(Num n, Num m){
    if(m > n - m) m = n - m;
    Num ans = 1, m2 = m;
    while (m2--) {
        ans *= n--;
        while (ans % m == 0 && m > 1)
            ans /= m--;
    }
    return ans;
}

Num solve() {
	return binom(n+m, n);
}

int main() {
#if BENCH
	freopen("files/poj1942_cb_paths_on_grid.txt","r",stdin);
#endif
	while (scanf("%lld%lld", &n, &m), n || m) {
		printf("%lld\n", solve());
	}
	return 0;
}
