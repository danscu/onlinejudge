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

typedef unsigned long Num;
const int maxr = 100006;
const Num MOD = 1000000007;

Num n, r;
Num P[32]; // 2^i % MOD
int A[maxr], B[maxr];

inline Num getPow(Num k) {
    Num res = 1;
    for (int i = 0; k; i++, k >>= 1)
        if (k & 1)
            res = (res * P[i]) % MOD;
    return res;
}

int main() {
#if BENCH
	freopen("files/2_hanoi.txt","r",stdin);
#endif
	Num p = 2;
	FOR(i, 0, 31) {
	    P[i] = p;
	    p = p * p % MOD;
	}
	int T;
	scanf("%d", &T);
	for (int tc = 0; tc < T; tc++) {
		scanf("%d%d", &n, &r);
		Num ans = 0, k = 1, m = n;
		Num last = 1;
		REP(i, r) {
		    scanf("%d%d", &A[i], &B[i]);
		    m -= B[i] - A[i];
		}
		REP(i, r) {
		    int a = A[i], b = B[i];
			if (a > last) {
			    // last .. a - 1 are all 1s
			    int c = a - last;
			    ans = (ans + getPow(m-k-c+1) * (getPow(c) - 1) % MOD) % MOD;
			    D("\t%d:%d +%d\n",k,c, getPow(m-k-c+1) * (getPow(c) - 1));
			    k += c;
			}
			ans = (ans + getPow(m-k) * (b - a + 1) % MOD) % MOD;
			D("\t%d(%d-%d) +%d\n",k,a,b,getPow(k-1) * (b - a + 1));
			k++;
			last = b + 1;
		}
		if (last < n) {
		    // last .. n
		    int c = n - last + 1;
		    ans = (ans + getPow(m-k-c+1) * (getPow(c) - 1) % MOD) % MOD;
		    D("\t%d:%d +%d\n",k,c, getPow(m-k-c+1) * (getPow(c) - 1));
		}
		printf("Case #%d\n", tc + 1);
		printf("%d\n", ans);
	}
	return 0;
}
